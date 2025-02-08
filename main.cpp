#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "game.hpp"

int main(int argc, char* argv[]) {

	Game game;

	while (game.isRunning()) {

		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return 0;
}