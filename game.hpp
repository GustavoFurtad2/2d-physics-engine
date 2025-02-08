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

		bool isAiming = false;
		bool justPressed = false;

		Circle* currentStone;

		void createStone();
		void updateStone(int x, int y);

		void drawSlingshot(SDL_Renderer* renderer);

		void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int sides, SDL_Color color);

		double degressToRadians(double degress);
};

#endif