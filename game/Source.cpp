#include "Game.h"

int main(int argc, char* argv[]) {

	/**/
	Game* game = Game::getInstance();

	if(game)
		game->GameLoop();

	game->ShutDown();
	return 0;
}