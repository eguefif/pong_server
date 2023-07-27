#pragma once
#include "def.hpp"
#include "client.hpp"

class Server
{
public:
	Server() = default;
	Server(std::string add, int aport);
	~Server();
	void run();

private:
	std::string address = "127.0.0.1";
	int port = 5000;
	int listening_socket = -1;
	struct pollfd *fds;
	int	nfds = 0;
	std::vector<Client> clients;
	int timeout = 500;
	bool running = true;

	int init();
	void onlisten();
	void init_listening();
	void handle_new_client();
	void handle_connexions();
	void cleanup();
	void read_client(int fd);
	void send_client(int fd);
	void remove_client(int fd);
	void process();
};
