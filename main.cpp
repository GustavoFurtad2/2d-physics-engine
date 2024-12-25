#include "game.hpp"

int main(int argc, char* argv[]) {

	Game *game = new Game();

	while (game->isRunning()) {

		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}