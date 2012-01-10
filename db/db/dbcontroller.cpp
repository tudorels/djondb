#include "dbcontroller.h"
#include "bson.h"
#include "util.h"
#include "fileinputoutputstream.h"
#include "fileinputstream.h"
#include "fileoutputstream.h"

#include "bsonoutputstream.h"
#include "bsoninputstream.h"

#include "cachemanager.h"
#include "indexfactory.h"
#include "index.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

DBController::DBController()
{
	_logger = getLogger(NULL);
}

DBController::~DBController()
{
	delete _logger;
}

void DBController::shutdown() {
	if (_logger->isInfo()) _logger->info("DBController shutting down");
	std::auto_ptr<FileOutputStream> fos(new FileOutputStream("djondb.dat", "wb"));
	for (std::map<std::string, SpacesType>::iterator i = _spaces.begin(); i != _spaces.end(); i++) {
		SpacesType space = i->second;
		std::string ns = space.ns;
		FILE_TYPE type = space.type;
		fos->writeString(ns);
		fos->writeInt(static_cast<int>(type));
		space.stream->close();
	}
	fos->close();
}

void DBController::initialize() {
	if (_logger->isInfo()) _logger->info("DBController initializing");
	std::auto_ptr<FileInputStream> fis(new FileInputStream("djondb.dat", "rb"));
	while (!fis->eof()) {
		std::auto_ptr<std::string> ns(fis->readString());
		FILE_TYPE type = static_cast<FILE_TYPE>(fis->readInt());

		StreamType* stream = open(*(ns.get()), type);
		long currentPos = stream->currentPos();
		if (type == INDEX_FTYPE) {
			stream->seek(0);
			IndexAlgorithm* impl = NULL;
			while (!stream->eof()) {
				BSONObj* obj = readBSON(stream);

				if (!impl) {
					impl = IndexFactory::indexFactory.index(ns->c_str(), *obj);
				}
				long indexPos = stream->readLong();
				long posData = stream->readLong();
				Index* index = impl->add(*obj, posData);
				index->indexPos = indexPos;
				delete obj;
			}
			stream->seek(currentPos);
		}
	}
	fis->close();
}

long DBController::checkStructure(BSONObj* obj) {
	Structure* structure = new Structure();
	for (std::map<t_keytype, BSONContent* >::const_iterator i = obj->begin(); i != obj->end(); i++) {
		structure->add(i->first);
	}

	StructureCache* cache = CacheManager::structuresCache();
	long strId = structure->crc();
	if (!cache->containsKey(strId)) {
		cache->add(strId, structure);
	} else {
		delete(structure);
	}
	return strId;
}

void DBController::writeBSON(StreamType* stream, BSONObj* obj) {
	if (_logger->isDebug()) _logger->debug(3, "DBController is writing bson to disc: %s", obj->toChar());

	auto_ptr<BSONOutputStream> out(new BSONOutputStream(stream));
	out->writeBSON(*obj);
	stream->flush();
}

BSONObj* DBController::readBSON(StreamType* stream) {
	auto_ptr<BSONInputStream> is(new BSONInputStream(stream));
	BSONObj* res = is->readBSON();
	if (_logger->isDebug()) _logger->debug(3, "DBController read bson from disc: %s", res->toChar());
	return res;
}

BSONObj* DBController::insert(char* ns, BSONObj* obj) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::insert ns: %s, bson: %s", ns, obj->toChar());
	StreamType* streamData = open(std::string(ns), DATA_FTYPE);

	BSONObj* result = NULL;
	if (!obj->has("_id")) {
		if (_logger->isDebug()) _logger->debug(2, "BSON does not contain an id, DBController is creating one");
		string* tid = uuid();
		std::string key("_id");
		obj->add(key, *tid);
		result = new BSONObj();
		result->add("_id", *tid);
		delete tid;
	}

	std::string* id = NULL;
	if (obj->type("_id") == STRING_TYPE) {
		id = obj->getString("_id");
	} else if (obj->type("_id") == PTRCHAR_TYPE) {
		id = new std::string(obj->getChars("_id"));
	}
	//    long crcStructure = checkStructure(obj);

	//    char* text = obj->toChar();
	//    streamData->writeChars(text, strlen(text));
	//    free(text);

	insertIndex(ns, obj, streamData->currentPos());

	writeBSON(streamData, obj);

	if (id != NULL) {
		CacheManager::objectCache()->add(*id, new BSONObj(*obj));
	}

	return result;
}

void DBController::update(char* ns, BSONObj* obj) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::update ns: %s, bson: %s", ns, obj->toChar());
	StreamType* streamData = open(std::string(ns), DATA_FTYPE);

	//    long crcStructure = checkStructure(obj);

	//    char* text = obj->toChar();
	//    streamData->writeChars(text, strlen(text));
	//    free(text);

	updateIndex(ns, obj, streamData->currentPos());

	writeBSON(streamData, obj);

	std::string* id = obj->getString("_id");

	CacheManager::objectCache()->add(*id, new BSONObj(*obj));
}

StreamType* DBController::open(std::string ns, FILE_TYPE type) {

	std::stringstream ss;
	ss << ns << ".";
	switch (type) {
		case DATA_FTYPE:
			ss << "dat";
			break;
		case INDEX_FTYPE:
			ss << "idx";
			break;
		case STRC_FTYPE:
			ss << "stt";
			break;
	}

	std::string fileName = ss.str();
	StreamType* stream = NULL;
	for (map<std::string, SpacesType>::iterator it = _spaces.begin(); it != _spaces.end(); it++) {
		std::string key = it->first;
		if (key.compare(fileName) == 0) {
			SpacesType space = it->second;
			stream = space.stream;
			break;
		}
	}
	if (stream != NULL) {
		return stream;
	}
	StreamType* output = new StreamType(fileName, "ab+");
	SpacesType space;
	space.ns = ns;
	space.stream = output;
	space.type = type;
	_spaces.insert(pair<std::string, SpacesType>(fileName, space));
	return output;
}

bool DBController::close(char* ns) {
	map<std::string, SpacesType>::iterator it = _spaces.find(std::string(ns));
	if (it != _spaces.end()) {
		SpacesType space = it->second;

		StreamType* stream = space.stream;
		stream->close();
		delete(stream);
		stream = 0;
		_spaces.erase(it);
	}
	return true;
}

void DBController::updateIndex(char* ns, BSONObj* bson, long filePos) {
	BSONObj indexBSON;
	indexBSON.add("_id", *bson->getString("_id"));
	IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
	Index* index = impl->find(indexBSON);

	index->posData = filePos;

	StreamType* out = open(ns, INDEX_FTYPE);
	long currentPos = out->currentPos();
	out->seek(index->indexPos);
	BSONObj* key = index->key;
	writeBSON(out, key);
	out->writeLong(index->indexPos);
	out->writeLong(index->posData);
	out->seek(currentPos);
}

void DBController::insertIndex(char* ns, BSONObj* bson, long filePos) {
	BSONObj indexBSON;
	std::string* id = bson->getString("_id");
	indexBSON.add("_id", *id);
	IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
	Index* index = impl->add(indexBSON, filePos);

	StreamType* out = open(std::string(ns), INDEX_FTYPE);
	index->indexPos = out->currentPos();
	BSONObj* key = index->key;
	writeBSON(out, key);
	out->writeLong(index->indexPos);
	out->writeLong(index->posData);
}

std::vector<BSONObj*> DBController::findFullScan(char* ns, const BSONObj& filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFullScan ns: %s, bsonFilter: %s", ns, filter.toChar());
	std::stringstream ss;
	ss << ns << ".dat";

	std::string filename = ss.str();

	FileInputStream* fis = new FileInputStream(filename.c_str(), "rb");
	std::vector<BSONObj*> result;

	BSONInputStream* bis = new BSONInputStream(fis);
	std::map<t_keytype, BSONContent* >::const_iterator testValIter = filter.begin();
	BSONContent* testVal = testValIter->second;
	t_keytype keyname = testValIter->first;

	// the first filter will be done over the file
	while (!fis->eof()) {
		BSONObj* readed = bis->readBSON();
		if (readed->has(keyname)) {
			BSONContent* content = readed->getContent(keyname);
			if (*content == *testVal) {
				if (_logger->isDebug()) _logger->debug(2, "found a match with key: %s, obj: %s", keyname.c_str(), readed->toChar());
				result.push_back(readed);
			}
		}
	}

	// now filter the results with the other keys
	testValIter++;
	for ( ;testValIter != filter.end(); testValIter++) {
		std::vector<BSONObj*> rsTmp;
		testVal = testValIter->second;
		keyname = testValIter->first;
		for (std::vector<BSONObj*>::iterator i = result.begin(); i != result.end(); i++) {
			BSONObj* obj = *i;
			if (obj->has(keyname)) {
				BSONContent* content = obj->getContent(keyname);
				if (*content == *testVal) {
					if (_logger->isDebug()) _logger->debug(2, "found a match with key: %s, obj: %s", keyname.c_str(), obj->toChar());
					rsTmp.push_back(obj);
				}
			}
		}
		result = rsTmp;
	}

	return result;
}

std::vector<BSONObj*> DBController::find(char* ns, const BSONObj& filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::find ns: %s, bsonFilter: %s", ns, filter.toChar());

	std::vector<BSONObj*> result;
	if (filter.has("_id")) {
		std::string* id = filter.getString("_id");

		BSONObj indexBSON;
		indexBSON.add("_id", *id);
		IndexAlgorithm* impl = IndexFactory::indexFactory.index(ns, indexBSON);
		Index* index = impl->find(indexBSON);

		if (index != NULL) {
			char fileName[255];
			memset(fileName, 0, 255);
			strcat(fileName, ns);
			strcat(fileName, ".");
			strcat(fileName, "dat");

			StreamType* out = open(ns, DATA_FTYPE);
			out->flush();
			//    out->close();

			StreamType* input = new StreamType(fileName, "rb");
			input->seek(index->posData);

			BSONObj* obj = readBSON(input);
			if (_logger->isDebug()) _logger->debug(2, "found a match using _id: %s", obj->toChar());
			result.push_back(obj);
			input->close();
		}
	} else {
		result = findFullScan(ns, filter);
	}

	return result;
}

BSONObj* DBController::findFirst(char* ns, BSONObj* filter) {
	if (_logger->isDebug()) _logger->debug(2, "DBController::findFirst ns: %s, bsonFilter: %s", ns, filter->toChar());
	std::string* id = filter->getString("_id");
	if (CacheManager::objectCache()->containsKey(*id)) {
		return (*CacheManager::objectCache())[*id];
	}
	std::vector<BSONObj*> temp = find(ns, *filter);
	if (temp.size() == 1) {
		BSONObj* element = *temp.begin();
		CacheManager::objectCache()->add(*id, new BSONObj(*element));
		return element;
	} else {
		return NULL;
	}
}

