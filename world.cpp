#include "world.hpp"
#include <iostream>

World::World(float gravity) {
    this->gravity = gravity;
}

World::~World() {
    for (Body* body : bodies) {
        delete body;
    }
}

void World::update() {

    for (Body* body : bodies) {

        body->update(bodies, this->gravity);
    }
}

Box* World::createBox(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, bool isDynamic) {

    Box* box = new Box(positionX, positionY, sizeX, sizeY, mass, gravity, isDynamic);

    bodies.push_back(box);

    return box;
}

Circle* World::createCircle(float positionX, float positionY, float radius, float mass, float gravity, bool isDynamic) {

    Circle* circle = new Circle(positionX, positionY, radius * 2, radius * 2, radius, mass, gravity, isDynamic);

    bodies.push_back(circle);

    return circle;
}
