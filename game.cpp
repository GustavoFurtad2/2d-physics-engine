#include "game.hpp"
#include <cmath>

Game::Game() : world(9.8f) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		window = SDL_CreateWindow("Demo - 2d physics engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);

		running = true;

		SDL_SetRenderDrawColor(renderer, 0, 166, 255, 255);

		world.createBox(0.0f, 500.f, 800.f, 100.f, 1.0f, world.gravity);
	}
}

void Game::createStone() {

	this->currentStone = world.createCircle(105.0f, 350.0f, 20.0f, 1.0f, world.gravity);
}

void Game::updateStone(int x, int y) {

	this->currentStone->positionX = x;
	this->currentStone->positionY = y;

}

Game::~Game() {
	
}

void Game::update() {

	world.update();
}

void Game::drawSlingshot(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 153, 94, 0, 255);

	SDL_Rect rect {
		100.0f,
		400.0f,
		10.0f,
		100.0f
	};

	SDL_RenderFillRect(renderer, &rect);

	rect.x = 75.0f;
	rect.y = 390.0f;
	rect.w = 60.0f;
	rect.h = 10.0f;

	SDL_RenderFillRect(renderer, &rect);

	rect.x = 65.0f;
	rect.y = 350.0f;
	rect.w = 10.0f;
	rect.h = 50.0f;

	SDL_RenderFillRect(renderer, &rect);

	rect.x = 135.0f;
	rect.y = 350.0f;
	rect.w = 10.0f;
	rect.h = 50.0f;

	SDL_RenderFillRect(renderer, &rect);

	if (currentStone) {
		SDL_RenderDrawLine(renderer, 105, 345, this->currentStone->positionX, this->currentStone->positionY);
		SDL_RenderDrawLine(renderer, 105, 355, this->currentStone->positionX, this->currentStone->positionY);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

double Game::degressToRadians(double degress) {
	return degress * 3.14 / 180.0;
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

	drawSlingshot(renderer);

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
	else if (event.type == SDL_MOUSEBUTTONDOWN) {

		if (event.button.button == SDL_BUTTON_LEFT) {

			isAiming = true;

			int x, y;
			int centerX = 105.0f;
			int centerY = 350.0f;

			SDL_GetMouseState(&x, &y);

			int deltaX = x - centerX;
			int deltaY = y - centerY;

			float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance <= 50.0f) {

				if (this->currentStone == nullptr) {
					createStone();
				}
			}
			else {
				world.createBox(x, y, 50.f, 50.f, 1.0f, world.gravity)->setDynamic(true);
			}
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {

		if (event.button.button == SDL_BUTTON_LEFT) { 

			if (isAiming) {
				isAiming = false;
			}

			int x, y;
			int centerX = 105.0f;
			int centerY = 350.0f;

			SDL_GetMouseState(&x, &y);

			int deltaX = x - centerX;
			int deltaY = y - centerY;
			float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

			float maxDistance = 50.0f;
			float forceMagnitude = std::min(distance, maxDistance);

			float directionX = -deltaX / distance;
			float directionY = -deltaY / distance;

			float forceX = (directionX * forceMagnitude) / 3;
			float forceY = (directionY * forceMagnitude) / 3;

			if (currentStone) {
				currentStone->setDynamic(true);
				currentStone->applyForce(forceX, forceY);
				currentStone = nullptr;
				isAiming = false;
			}
		}
	}

	if (isAiming) {

		int x, y;
		int centerX = 105.0f;
		int centerY = 350.0f;

		SDL_GetMouseState(&x, &y);

		int deltaX = x - centerX;
		int deltaY = y - centerY;
		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance <= 50.0f) {
			updateStone(x, y);
		}
	}
}