#include "game.hpp"

Game::Game(Client *aplayer) :
	player1(aplayer)
{}

void Game::add_player(Client *aplayer)
{
	player2 = aplayer;
	status = FULL;
}

int Game::get_status()
{
	return (status);
}
