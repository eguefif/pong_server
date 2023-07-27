#pragma once
#include "def.hpp"
#include "client.hpp"
#include "game.hpp"

class Server
{
public:
	Server() = default;
	Server(std::string add, int aport);
	enum e_status {WAITING_FOR_PLAYER = 0, PLAYING = 1, PAUSE = 2, FINISHED = 3, FULL = 4};
	~Server();
	void run();

private:
	std::string address = "127.0.0.1";
	int port = 5000;
	int listening_socket = -1;
	struct pollfd *fds;
	int	nfds = 0;
	std::vector<int> sockets;
	std::vector<Game> games;
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
	void add_new_client(int fd, struct sockaddr_in *client);
	void remove_client(int fd);
	void process();
};
