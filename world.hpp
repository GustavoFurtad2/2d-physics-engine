#pragma once

#include <vector>

#include "Body.hpp"

class World {

	public:

		World(float gravity);
		~World();

		float gravity;

		void update();

		Box* createBox(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity);
		Circle* createCircle(float positionX, float positionY, float radius, float mass, float gravity);

		std::vector<Body*> bodies;

};