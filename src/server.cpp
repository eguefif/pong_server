#include "server.hpp"

Server::Server(std::string add, int aport) :
	address(add), port(aport)
{}

Server::~Server()
{
}

void Server::run()
{
	init();
	onlisten();
}

int Server::init()
{
	struct sockaddr_in s_address;
	int opt = 1;

	memset(&s_address, '\0', sizeof(s_address));
	listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket < 0)
	{
		std::cerr << "Impossible to create socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	to_non_blocking(listening_socket);
	if (setsockopt(listening_socket,
				SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT,
				&opt, sizeof(opt)))
	{
		std::cerr << "Impossible to set socket to reuse" << std::endl;
		exit(EXIT_FAILURE);
	}
	s_address.sin_family = AF_INET;
	s_address.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), &(s_address.sin_addr.s_addr));
	if (bind(listening_socket, (struct sockaddr*) &s_address, sizeof(s_address)) < 0)
	{
		std::cerr << "Impossible to bind listening socket: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(listening_socket, 5) < 0)
	{
		std::cerr << "impossible to set listening socket to listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	nfds = 1;
	return (1);
}

void Server::onlisten()
{
	int ready;

	while (running)
	{
		init_listening();
		ready = poll(fds, nfds, timeout);
		if (ready < 0)
		{
			std::cerr << "Impossible to poll" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (ready == 0)
			continue;
		handle_new_client();
		handle_connexions();
		process();
		free(fds);
	}
}

void Server::init_listening()
{
	size_t size;
	int i = 1;

	size = 1 + sockets.size();
	fds = (struct pollfd *) calloc(size, sizeof(struct pollfd));
	fds[0].fd = listening_socket;
	fds[0].events = POLLIN;
	for (auto socket : sockets)
	{
		fds[i].fd = socket;
		fds[i].events = POLLIN | POLLOUT | POLLRDHUP;
		i++;
	}
}

void Server::handle_new_client()
{
	struct sockaddr_in client;
	int fd;
	socklen_t client_len = sizeof(client);

	if (fds[0].revents & POLLIN)
	{
		memset(&client, '\0', sizeof(client));
		fd = accept(listening_socket,(struct sockaddr*) &client, &client_len);
		if (fd < -1)
			std::cerr << "Error while accepting new client" << std::endl;
		else
		{
			add_new_client(fd, &client);
		}
	}
}

void Server::add_new_client(int fd, struct sockaddr_in *client)
{
	sockets.push_back(fd);
	nfds++;
	for (auto &game : games)
	{
		if (game.get_status() == WAITING_FOR_PLAYER)
		{
			Client new_client(fd, client);
			game.add_player(new_client);
			return;
		}
	}
	Game game(fd, client);
	games.push_back(game);
}

void Server::handle_connexions()
{
	for (int i = 1; i < nfds ; i++)
	{
		if (fds[i].revents & POLLIN)
			read_client(fds[i].fd);
		if (fds[i].revents & POLLOUT)
			send_client(fds[i].fd);
		if (fds[i].revents & POLLHUP || fds[i].revents & POLLERR || fds[i].revents & POLLRDHUP)
			set_game_to_disconnect(fds[i].fd);
	}
}

void Server::read_client(int fd)
{
	for (auto &game : games)
		game.read_message(fd);
}

void Server::send_client(int fd)
{
	for (auto &game : games)
		game.send_message(fd);
}

void Server::process()
{
	garbage_games();
	for (auto &game : games)
		game.update();
}

void Server::garbage_games()
{
	std::vector<std::vector<Game>::iterator> game_to_delete;

	for (auto game = games.begin(); game != games.end(); ++game)
		if (game->get_status() == 5)
			game_to_delete.push_back(game);
	for (auto game : game_to_delete)
	{
		games.erase(game);
		std::cout << "Erasing game" << std::endl;
	}
	game_to_delete.clear();
}

void Server::cleanup()
{
	close(listening_socket);
	for (auto &game : games)
		game.cleanup();
	games.clear();
	sockets.clear();
}

void Server::set_game_to_disconnect(int fd)
{
	for (auto &game : games)
	{
		if (game.is_player_socket(fd))
			game.set_to_disconnect();
	}
}
