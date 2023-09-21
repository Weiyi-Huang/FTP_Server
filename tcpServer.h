#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class tcpServer
{
public:
	tcpServer(unsigned port);
	~tcpServer() = default;
	bool createSocket();
	bool bindSocket();
	bool listenSocket();
	SOCKET acceptClient();
	void closeSocket();
private:
	SOCKET m_fd;
	unsigned m_port;
};
#endif