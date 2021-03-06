// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include "networkoutputstream.h"

#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include "util.h"
#include <errno.h>
#include <assert.h>
#include <limits.h>
#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <unistd.h>
#endif

#ifdef LINUX 
	int __sendFlags_networkoutput = MSG_NOSIGNAL;
#else
	int __sendFlags_networkoutput = MSG_DONTROUTE;
#endif

// Windows does not define this flag
#ifndef SHUT_RDWR
	#define SHUT_RDWR 2 // SD_BOTH
#endif

int MAX_ALLOWED = 1024;

using namespace std;

NetworkOutputStream::NetworkOutputStream()
{
	_logger = getLogger(NULL);
	_bufferStream = new MemoryStream(2048);
}

NetworkOutputStream::~NetworkOutputStream()
{
	delete _bufferStream;
}

NetworkOutputStream::NetworkOutputStream(int socket)
{
	_logger = getLogger(NULL);
	_socket = socket;
	_bufferStream = new MemoryStream(2048);
}

NetworkOutputStream::NetworkOutputStream(const NetworkOutputStream& orig) {
	this->_socket = orig._socket;
	_logger = getLogger(NULL);
	_bufferStream = orig._bufferStream;
}


/* Write 1 byte in the output */
void NetworkOutputStream::writeChar (unsigned char v)
{
	_bufferStream->writeChar(v);
}

/* Write 1 bytes in the output (little endian order) */
void NetworkOutputStream::writeBoolean (bool v)
{
	writeData<char>((char)v);
}

/* Write 2 bytes in the output (little endian order) */
void NetworkOutputStream::writeShortInt (__int16 v)
{
	writeData<__int16>(v);
}

/* Write 4 bytes in the output (little endian order) */
void NetworkOutputStream::writeInt (__int32 v)
{
	writeData<__int32>(v);
}

/* Write 8 bytes in the output (little endian order) */
void NetworkOutputStream::writeLong (__int64 v)
{
	writeData<__int64>(v);
}

/* Write a 4 byte float in the output */
void NetworkOutputStream::writeFloatIEEE (float v)
{
	_bufferStream->writeFloatIEEE(v);
}

/* Write a 8 byte double in the output */
void NetworkOutputStream::writeDoubleIEEE (double v)
{
	_bufferStream->writeDoubleIEEE(v);
}

void NetworkOutputStream::writeChars(const char *text, __int32 len) {
	_bufferStream->writeChars(text, len);
}

void NetworkOutputStream::writeString(const std::string& text) {
	_bufferStream->writeString(text);
}

int NetworkOutputStream::open(const char* hostname, int port)
{

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	portno = port;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		_logger->error(std::string("ERROR opening socket"));
		return -1;
	}
	server = gethostbyname(hostname);
	if (server == NULL) {
		_logger->error(std::string("ERROR, no such host\n"));
		return -1;
	}
	memset((char *) & serv_addr, 0, sizeof (serv_addr));
	serv_addr.sin_family = AF_INET;
#ifdef WINDOWS
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
	memcpy((char *) & serv_addr.sin_addr.s_addr,
			(char *) server->h_addr,
			server->h_length);
#endif
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (sockaddr *) & serv_addr, sizeof (serv_addr)) < 0) {
		int error;
#ifdef WINDOWS
		error = WSAGetLastError();
#else
		error = 0;
#endif
		_logger->error("ERROR connecting: %d", error);
		return -1;
	}
	_socket = sockfd;

	return sockfd;
}

void NetworkOutputStream::closeStream() {
	shutdown(_socket, SHUT_RDWR);
#ifndef WINDOWS
	close(_socket);
#else
	closesocket(_socket);
#endif
}

int NetworkOutputStream::setNonblocking() {
	int flags;

	/* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
	/* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
	if (-1 == (flags = fcntl(_socket, F_GETFL, 0)))
		flags = 0;
	return fcntl(_socket, F_SETFL, flags | O_NONBLOCK);
#else
#ifndef WINDOWS
	/* Otherwise, use the old way of doing it */
	flags = 1;
	return ioctl(_socket, FIOBIO, &flags);
#else
	u_long f = 1;
	return ioctlsocket(_socket, FIONBIO, &f);
#endif
#endif
}

int NetworkOutputStream::disableNagle() {
	/* Disable the Nagle (TCP No Delay) algorithm */

	int flag = 1;

	int ret = setsockopt( _socket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag) );
	return ret;
}

void NetworkOutputStream::checkBuffer() {
	if (_bufferStream->size() > MAX_ALLOWED) {
		flush();
	}
}

void NetworkOutputStream::flush() {
	int size = _bufferStream->size();
	if (size > 0) {
		char* data = _bufferStream->toChars();
		if (send(_socket, data, size, __sendFlags_networkoutput) < 0) {
			throw DjondbException(errno, strerror(errno));
		}
	}
	_bufferStream->reset();
}
