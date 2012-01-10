#include "connection.h"

#include "networkinputstream.h"
#include "networkoutputstream.h"
#include "commandwriter.h"
#include "insertcommand.h"
#include "findcommand.h"
#include "updatecommand.h"
#include "bsoninputstream.h"
#include "connectionmanager.h"
#include "util.h"

using namespace djondb;

Connection::Connection(std::string host)
{
	_host = host;
	_inputStream = NULL;
	_outputStream = NULL;
	_commandWriter = NULL;
	_open = false;
	_logger = getLogger(NULL);
}

Connection::Connection(const Connection& orig) {
	this->_host = orig._host;
	this->_inputStream = orig._inputStream;
	this->_open =  orig._open;
	this->_outputStream = orig._outputStream;
	this->_commandWriter = orig._commandWriter;
	_logger = getLogger(NULL);
}

Connection::~Connection()
{
	internalClose();
	delete _logger;
}

bool Connection::open() {
	if (_logger->isDebug()) _logger->debug("Openning connection");
	_outputStream = new NetworkOutputStream();
	int socket = _outputStream->open(_host.c_str(), 1243);
	if (socket > 0) {
		_inputStream = new NetworkInputStream(socket);
		_open = true;
		_commandWriter = new CommandWriter(_outputStream);
		if (_logger->isDebug()) _logger->debug("Connection opened");
		return true;
	} else {
		delete _outputStream;
		return false;
	}
}

void Connection::close() { 
	if (_logger->isDebug()) _logger->debug("Closing connection");
	ConnectionManager::releaseConnection(this);
	_open = false;
}

void Connection::internalClose() {
	if (_open) {
		_inputStream->closeStream();
		_outputStream->closeStream();
		if (_inputStream)   {
			delete (_inputStream);
			_inputStream = NULL;
		}
		if (_outputStream)  {
			delete (_outputStream);
			_outputStream = NULL;
		}
		if (_commandWriter) {
			delete (_commandWriter);
			_commandWriter = NULL;
		}
		_open = false;
	}
}

bool Connection::insert(const std::string& ns, const std::string& json) {
	if (_logger->isDebug()) _logger->debug(2, "Insert command. ns: %s, json: %s", ns.c_str(), json.c_str());
	BSONObj* obj = BSONParser::parse(json);
	bool result = insert(ns, *obj);
	delete obj;
	return result;
}

bool Connection::insert(const std::string& ns, const BSONObj& bson) {
	if (_logger->isDebug()) _logger->debug(2, "Insert command. ns: %s, bson: %s", ns.c_str(), bson.toChar());
	InsertCommand cmd;
	cmd.setBSON(bson);
	cmd.setNameSpace(ns);
	_commandWriter->writeCommand(&cmd);

	// When the bson didnt contain an id the server will return a bson with it
	if (!bson.has("_id")) {
		if (_logger->isDebug()) _logger->debug(2, "Server answered with a new id, dropping it");
		BSONInputStream tmpIS(_inputStream);
		tmpIS.readBSON(); 
		// drop it
		// temporal solution, later I will need to do something with the return
	}
	return true;
}

bool Connection::update(const std::string& ns, const std::string& json) {
	if (_logger->isDebug()) _logger->debug(2, "Update command. ns: %s, json: %s", ns.c_str(), json.c_str());
	BSONObj* obj = BSONParser::parse(json);
	bool result = update(ns, *obj);
	delete obj;
	return result;
}

bool Connection::update(const std::string& ns, const BSONObj& obj) {
	if (_logger->isDebug()) _logger->debug(2, "Update command. ns: %s, bson: %s", ns.c_str(), obj.toChar());
	UpdateCommand cmd;
	cmd.setBSON(obj);
	cmd.setNameSpace(ns);

	_commandWriter->writeCommand(&cmd);

	return true;
}

BSONObj* Connection::findByKey(const std::string& ns, const std::string& id) {
	if (_logger->isDebug()) _logger->debug("executing findByKey ns: %s id: %s", ns.c_str(), id.c_str());

	BSONObj filter;
	filter.add("_id", id);

	std::vector<BSONObj*> result = find(ns, filter);

	BSONObj* res = NULL;
	if (result.size() == 1) {
		if (_logger->isDebug()) _logger->debug(2, "findByKey found 1 result");
		res = *result.begin();
	} else {
		if (result.size() > 1) {
			throw "The result contains more than 1 result";
		}
	}
	return res;
}

std::vector<BSONObj*> Connection::find(const std::string& ns, const std::string& filter) {
	if (_logger->isDebug()) _logger->debug("executing find ns: %s, filter: %s", ns.c_str(), filter.c_str());

	BSONObj* bsonFilter = BSONParser::parse(filter);

	std::vector<BSONObj*> result = find(ns, *bsonFilter);
	delete bsonFilter;
	return result;
}

std::vector<BSONObj*> Connection::find(const std::string& ns, const BSONObj& bsonFilter) {
	if (_logger->isDebug()) _logger->debug("executing find ns: %s, bsonFilter: %s", ns.c_str(), bsonFilter.toChar());
	FindCommand cmd;
	cmd.setBSON(bsonFilter);
	cmd.setNameSpace(ns);
	_commandWriter->writeCommand(&cmd);

	BSONInputStream is(_inputStream);

	std::vector<BSONObj*> result = is.readBSONArray();

	return result;
}


bool Connection::isOpen() const {
	return _open;
}

std::string Connection::host() const {
	return _host;
}
