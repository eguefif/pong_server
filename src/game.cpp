#include "game.hpp"

Game::Game(int fd, struct sockaddr_in *info) :
	player1(fd, info)
{
	Message message("waiting", "");
	player1.outbound_messages.push(message);
	std::cout << "Creating a new game. Player 1: " << player1.get_name() << std::endl;
	srand(time(NULL));
	ball_direction = rand() % 4;
}

void Game::add_player(Client aplayer)
{
	Message message("join", "");
	player2 = aplayer;
	player2.outbound_messages.push(message);
	status = INIT;
	message.set_command("full");
	player2.outbound_messages.push(message);
	player1.outbound_messages.push(message);
	std::cout << "Game with " << player1.get_name() << " is full with " << player2.get_name() << std::endl;
}

int Game::get_status()
{
	return (status);
}

void Game::cleanup()
{
	player1.cleanup();
	if (status != WAITING_FOR_PLAYER)
		player2.cleanup();
}

void Game::read_message(int fd)
{
	if (player1.get_sock() == fd)
		player1.read_all();
	else if (player2.get_sock() == fd)
		player2.read_all();
}

void Game::send_message(int fd)
{
	if (player1.get_sock() == fd)
		player1.send_all();
	else if (player2.get_sock() == fd)
		player2.send_all();
}

void Game::update()
{
	if (status == WAITING_FOR_PLAYER)
		return ;
	else if (status == INIT)
		init();
	else if (status == PLAYING)
		playing();
	else if (status == PAUSE)
		pause();
	else if (status == FINISHED)
		finished();
}

void Game::init()
{
	if (!(init_flag & BALL))
	{
		Message message("ball", std::to_string(ball_direction));
		broadcast(message);
		init_flag |= BALL;
	}
	if (!(init_flag & NAME1))
	{
		if (player1.check_and_set_name())
		{
			std::cout << "Name: " << player1.get_name() << std::endl;
			Message message("name", player1.get_name());
			player2.outbound_messages.push(message);
			init_flag |= NAME1;
		}
	}
	if (!(init_flag & NAME2))
	{
		if (player2.check_and_set_name())
		{
			std::cout << "Name: " << player2.get_name() << std::endl;
			Message message("name", player2.get_name());
			player1.outbound_messages.push(message);
			init_flag |= NAME2;
		}
	}
	if (!(init_flag & READY1))
	{
		if (player1.is_ready())
		{
			std::cout << "Ready1"<< std::endl;
			init_flag |= READY1;
		}
	}
	if (!(init_flag & READY2))
	{
		if (player2.is_ready())
		{
			std::cout << "Ready2"<< std::endl;
			init_flag |= READY2;
		}
	}
	if (is_init_done())
	{
		std::cout << "Game starting" << std::endl;
		status = PLAYING;
		send_start_game();
	}
}

bool Game::is_init_done()
{
	return ((init_flag & BALL) \
			&& (init_flag & NAME1) \
			&& (init_flag & NAME2) \
			&& (init_flag & READY1) \
			&& (init_flag & READY2) \
			);
}

void Game::send_start_game()
{
	Message message("start", "");
	broadcast(message);
}

void Game::playing()
{

}

void Game::pause()
{}

void Game::finished()
{}

void Game::broadcast(Message message)
{
	player1.outbound_messages.push(message);
	player2.outbound_messages.push(message);
}
