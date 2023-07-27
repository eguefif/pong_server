#pragma once
#include "def.hpp"
#include "client.hpp"

class Game
{
public:
	Game(Client *aplayer);
	enum e_status {WAITING_FOR_PLAYER = 0, PLAYING = 1, PAUSE = 2, FINISHED = 3, FULL = 4};
	void add_player(Client *aplayer);
	int get_status();

private:
	Client *player1;
	Client *player2;
	int		status = WAITING_FOR_PLAYER;
};
