#include "ftpServer.h"

ftpServer::ftpServer(unsigned port) :m_connections(0), m_maxconnections(MAXCONN)
{
	// setup server
	m_listening = new tcpServer(port);
	if (!m_listening->createSocket()) {
		m_listening->closeSocket();
	}
	if (!m_listening->bindSocket()) {
		m_listening->closeSocket();
	}
	if (!m_listening->listenSocket()) {
		m_listening->closeSocket();
	}
	// accept clients initialize
	m_clients = std::vector<ftpConnection *>{};
}
ftpServer::~ftpServer()
{
	delete m_listening;
}

void ftpServer::startServer()
{
	while (m_connections < m_maxconnections) {
		connectHandle();
		for (auto iter = m_clients.begin(); iter != m_clients.end();) {
			if (!(*iter)->getConnectActive()) {
				iter = m_clients.erase(iter);
				--m_connections;
			}
			else {
				++iter;
			}
		}
		std::cout << "The connection number are " << m_connections << std::endl;
	}
}

void ftpServer::connectHandle()
{
	SOCKET connectfd = m_listening->acceptClient();
	ftpConnection *client = new ftpConnection(connectfd);
	m_clients.push_back(client);
	++m_connections;
	std::thread t(&ftpConnection::commandPI, client);
	t.detach();
}