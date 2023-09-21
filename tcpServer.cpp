#include "tcpServer.h"

tcpServer::tcpServer(unsigned port) :m_fd(INVALID_SOCKET), m_port(port)
{
}

bool tcpServer::createSocket()
{
	// initialize winSock
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		std::cerr << "WSAStartup failed with error: " << err << std::endl;
		return false;
	}
	// create socket
	m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_fd == INVALID_SOCKET) {
		std::cerr << "socket function failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	// set socket
	int iOptVal = 1;
	if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (char *)(&iOptVal), sizeof(int)) == SOCKET_ERROR) {
		std::cerr << "setsockopt for SO_REUSEADDR failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	if (setsockopt(m_fd, SOL_SOCKET, SO_KEEPALIVE, (char *)(&iOptVal), sizeof(int)) == SOCKET_ERROR) {
		std::cerr << "setsockopt for SO_KEEPALIVE failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	std::cout << "createSocket() successful\n";
	return true;
}
bool tcpServer::bindSocket()
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htonl(INADDR_ANY);
	service.sin_port = htons(m_port);
	if (bind(m_fd, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cerr << "bind function failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	std::cout << "bindSocket() successful\n";
	return true;
}
bool tcpServer::listenSocket()
{
	if (listen(m_fd, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "listen function failed with error: " << WSAGetLastError() << std::endl;
		return false;
	}
	std::cout << "listenSocket() successful\n";
	return true;
}
SOCKET tcpServer::acceptClient()
{
	SOCKET AcceptSocket;
	struct sockaddr_in client;
	int addrlen = sizeof(client);
	AcceptSocket = accept(m_fd, (SOCKADDR *)&client, &addrlen);
	if (AcceptSocket == INVALID_SOCKET)
	{
		std::cerr << "accept function failed with error: " << WSAGetLastError() << std::endl;
		return INVALID_SOCKET;
	}
	// acquire client information
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip));
	std::cout << "\nAccepted connection from " << ip << ": " << htons(client.sin_port) << std::endl;
	return AcceptSocket;
}
void tcpServer::closeSocket()
{
	closesocket(m_fd);
	WSACleanup();
}