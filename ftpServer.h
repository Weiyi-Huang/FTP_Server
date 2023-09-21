#ifndef FTPSERVER_H
#define FTPSERVER_H

#include "tcpServer.h"
#include "ftpConnection.h"
#include <vector>
#include <thread>

constexpr int MAXCONN = 10;

class ftpServer
{
public:
	ftpServer(unsigned port);
	~ftpServer();
	void startServer();
private:
	void connectHandle();
private:
	tcpServer *m_listening;
	int m_connections;
	const int m_maxconnections;
	std::vector<ftpConnection *> m_clients;
};
#endif