#include <vector>
#include "body.hpp"
#include "collision.hpp"
#include <iostream>

Body::Body(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, std::string type, bool isDynamic)
    : positionX(positionX),
    positionY(positionY),
    sizeX(sizeX),
    sizeY(sizeY),
    mass(mass),
    gravity(gravity),
    type(type),
    isDynamic(isDynamic),
    isCollidingLeft(false),
    isCollidingRight(false),
    isCollidingTop(false),
    isCollidingBottom(false),
    forceX(0),
    forceY(0)
{}

Box::Box(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, bool isDynamic)
    : Body(positionX, positionY, sizeX, sizeY, mass, gravity, "Box", isDynamic) {

    applyForce(0, this->gravity);
}

Box::~Box() {}

void Box::update(std::vector<Body*> bodies, float gravity) {

    if (this->isDynamic) {

        this->isCollidingLeft = false;
        this->isCollidingRight = false;
        this->isCollidingTop = false;
        this->isCollidingBottom = false;

        for (Body* body : bodies) {

            if (body != this) {

                if (body->type == "Box") {

                    Rect rect1 = {
                        this->positionX,
                        this->positionY,
                        this->sizeX,
                        this->sizeY
                    };

                    Rect rect2 = {
                        body->positionX,
                        body->positionY,
                        body->sizeX,
                        body->sizeY
                    };

                    if (!body->isDynamic) {
                        this->isCollidingLeft = boxCollideLeftBox(rect1, rect2);
                        this->isCollidingRight = boxCollideRightBox(rect1, rect2);
                    }

                    this->isCollidingTop = boxCollideTopBox(rect1, rect2);
                    this->isCollidingBottom = boxCollideBottomBox(rect1, rect2);

                    if (!this->isCollidingLeft || !this->isCollidingRight) {

                        this->positionX += this->forceX;

                        rect1 = {
                            this->positionX,
                            this->positionY,
                            this->sizeX,
                            this->sizeY
                        };

                        this->isCollidingLeft = boxCollideLeftBox(rect1, rect2);
                        this->isCollidingRight = boxCollideRightBox(rect1, rect2);

                        if (this->isCollidingLeft || this->isCollidingRight) {

                            body->forceX += this->forceX;

                            this->forceX = 0;

                        }
                    }

                    if (!this->isCollidingBottom) {
                        this->positionY += this->forceY;
                    }
                    else {
                        this->forceY = 0;
                    }
                }
            }
        }
    }
}

void Box::applyForce(float x, float y) {

    this->forceX += (this->mass * x) / 100;
    this->forceY += (this->mass * y) / 100;
}

Circle::Circle(float positionX, float positionY, float sizeX, float sizeY, float radius, float mass, float gravity, bool isDynamic)
    : Body(positionX, positionY, radius * 2, radius * 2, mass, gravity, "Circle", isDynamic), radius(radius) {}

Circle::~Circle() {}

void Circle::update(std::vector<Body*> bodies, float gravity) {

}