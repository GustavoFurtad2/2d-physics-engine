#pragma once

#include <vector>

#include "Body.hpp"

class World {

	public:

		World(float gravity);
		~World();

		float gravity;

		void update();

		Box* createBox(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, bool isDynamic);
		void createCircle(float positionX, float positionY, float radius, float mass, float gravity, bool isDynamic);

		std::vector<Body*> bodies;

};