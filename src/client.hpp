#pragma once
#include "def.hpp"
#include "tcpstream.hpp"

class Client
{
public:
	Client(int fd, struct sockaddr_in *info);
	int get_sock();
	void send_all();
	void read_all();
	std::queue<std::string> inbound_messages;
	void cleanup();

private:
	TCP_Stream stream;
	std::string protoheader = "";
	std::string message = "";
	int size = 0;
	int message_read_size = 0;
	int protoheader_read_size = 0;

	void read_protoheader();
};
