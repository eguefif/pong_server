#pragma once
#include "def.hpp"
#include "tcpstream.hpp"
#include "message.hpp"

class Client
{
public:
	Client() = default;
	Client(int fd, struct sockaddr_in *info);
	enum sides {LEFT = 0, RIGHT = 1};
	int get_sock();
	std::string get_name();
	void send_all();
	void read_all();
	std::vector<Message> inbound_messages;
	std::queue<Message> outbound_messages;
	void cleanup();
	bool check_and_set_name();
	bool is_ready();

private:
	std::string name = "";
	int side;
	TCP_Stream stream;
	std::string protoheader = "";
	std::string message = "";
	int size = 0;
	int message_read_size = 0;
	int protoheader_read_size = 0;

	void read_protoheader();
};
