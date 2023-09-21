#include "ftpServer.h"

int main()
{
	unsigned port = 21;
	ftpServer server(port);
	server.startServer();

	return 0;
}