#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
#include <iostream>
#include "world.hpp"

class Game {

	public:

		Game();
		~Game();

		void clean();
		void update();
		void render();
		void handleEvents();

		bool isRunning() {
			return running;
		};

	private:

		World world;

		bool running;
		SDL_Window* window;
		SDL_Renderer* renderer;

};

#endif