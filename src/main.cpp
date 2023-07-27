#include "def.hpp"
#include "server.hpp"

int main(int argc, char *argv[])
{
	std::string address;
	int port;

	if (argc == 3)
	{
		address = argv[1];
		port = atoi(argv[2]);
		Server server(address, port);
		server.run();
	}
	else
	{
		Server server;
		server.run();
	}
	return (1);
}
