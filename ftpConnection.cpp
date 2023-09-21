#include "ftpConnection.h"

ftpConnection::ftpConnection(SOCKET fd) :m_fd(fd), m_active(true)
{
}

bool ftpConnection::getConnectActive()
{
	return m_active;
}

void ftpConnection::commandPI()
{
	std::string reply = "220 Service ready!\r\n";
	std::cout << "----> " << reply << std::endl;
	sendBuffer(reply);

	char transmit[COMMANDSIZE] = { 0 };
	recvBuffer(transmit);
	std::cout << "<----" << transmit << std::endl;
	reply = "200 Always in UTF8 mode.\r\n";
	std::cout << "----> " << reply << std::endl;
	sendBuffer(reply);

	m_active = false;

	//while (m_active) {
	//	memset(transmit, 0, COMMANDSIZE);
	//	recvBuffer(transmit);
	//	std::cout << "<----" << transmit << std::endl;
	//	//authenticate();
	//}
}
void ftpConnection::authenticate()
{
}

int ftpConnection::sendBuffer(std::string message)
{
	int bytes = ::send(m_fd, message.c_str(), static_cast<int>(message.size()), 0);
	if (bytes == SOCKET_ERROR) {
		std::cerr << "send function failed with error: " << WSAGetLastError() << std::endl;
		return 0;
	}
	return bytes;
}
int ftpConnection::recvBuffer(char message[])
{
	
	int bytes = ::recv(m_fd, message, COMMANDSIZE, 0);
	if (bytes == SOCKET_ERROR) {
		std::cerr << "recv function failed with error: " << WSAGetLastError() << std::endl;
		return 0;
	}
    return bytes;
}