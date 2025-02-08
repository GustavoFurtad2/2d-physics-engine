#include "game.hpp"
#include <cmath>

Game::Game() : world(9.8f) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		window = SDL_CreateWindow("Demo - 2d physics engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);

		running = true;

		SDL_SetRenderDrawColor(renderer, 0, 166, 255, 255);

		/*
		world.createBox(110.0f, 200.f, 100.f, 100.f, 1.0f, world.gravity, true)->applyForce(2, 0);

		world.createBox(400.0f, 400.f, 100.f, 100.f, 1.0f, world.gravity, true);

		world.createBox(0.0f, 500.f, 800.f, 100.f, 1.0f, world.gravity, false);
		*/

		world.createCircle(130.0f, 100.0f, 50.0f, 1.0f, world.gravity, true);
		world.createCircle(530.0f, 400.0f, 50.0f, 1.0f, world.gravity, true);

		//world.createBox(100.0f, 100.f, 50.f, 50.f, 1.0f, world.gravity, true);

		world.createBox(0.0f, 500.f, 800.f, 100.f, 1.0f, world.gravity, false);

	}
}

Game::~Game() {
	
}

void Game::update() {

	world.update();
}

void Game::drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, int sides, SDL_Color color) {

	if (sides < 3) {
		sides = 3;
	}

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	const float PI = 3.14159265f;
	float angleStep = 2 * PI / sides;

	int prevX = centerX + radius * cos(0);
	int prevY = centerY + radius * sin(0);

	for (int i = 1; i <= sides; i++) {

		float angle = i * angleStep;

		int nextX = centerX + radius * cos(angle);
		int nextY = centerY + radius * sin(angle);

		SDL_RenderDrawLine(renderer, prevX, prevY, nextX, nextY);

		prevX = nextX;
		prevY = nextY;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Game::render() {

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (Body* body : world.bodies) {

		if (body->type == "Box") {

			SDL_Rect rect {
				body->positionX,
				body->positionY,
				body->sizeX,
				body->sizeY,
			};

			SDL_RenderFillRect(renderer, &rect);
		}
		else if (body->type == "Circle") {

			drawCircle(renderer, body->positionX, body->positionY, body->radius, 50, {255, 0, 0, 255});
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 166, 255, 255);

	SDL_RenderPresent(renderer);
}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

void Game::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {

		running = false;
	}
}