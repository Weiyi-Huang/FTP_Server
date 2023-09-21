#ifndef FTPCONNECTION_H
#define FTPCONNECTION_H

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <string>
#include <atomic>

constexpr unsigned COMMANDSIZE = 64;

class ftpConnection
{
public:
	ftpConnection(SOCKET fd);
	bool getConnectActive();
	void commandPI();
private:
	void authenticate();
	int sendBuffer(std::string message);
	int recvBuffer(char message[]);
private:
	SOCKET m_fd;
	std::atomic<bool> m_active;
};
#endif