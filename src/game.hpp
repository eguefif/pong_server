#pragma once
#include "def.hpp"
#include "client.hpp"

class Game
{
public:
	Game(int fd, struct sockaddr_in * info);
	enum e_status {WAITING_FOR_PLAYER = 0,
		INIT = 1,
		READY = 2,
		PLAYING = 3,
		PAUSE = 4,
		FINISHED = 5
	};
	enum e_init_flag {
		BALL = 1 << 0,
		NAME1 = 1 << 1,
		NAME2 = 1 << 2,
		READY1 = 1 << 3,
		READY2 = 1 << 4
	};
	void add_player(Client aplayer);
	int get_status();
	void update();
	void cleanup();
	void read_message(int fd);
	void send_message(int fd);

private:
	Client	player1;
	Client	player2;
	int		status = WAITING_FOR_PLAYER;
	int		ball_direction;
	int		init_flag = 0;

	void init();
	bool is_init_done();
	void send_start_game();
	void playing();
	void pause();
	void finished();
	void broadcast(Message message);
};
