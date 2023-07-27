#pragma once
#include "def.hpp"

class TCP_Stream
{
public:
	TCP_Stream() = default;
	TCP_Stream(int asock, struct sockaddr_in *info);
	size_t sendto(const char *buffer, size_t len);
	size_t receive(char *buffer, size_t len);
	int get_sock();
	std::string get_addr();
	int get_port();
	void cleanup();

private:
	int sock;
	std::string peer_add;
	int peer_port;
};
