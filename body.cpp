#include <vector>
#include "body.hpp"
#include "collision.hpp"
#include <iostream>
#include <cmath>

Body::Body(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, std::string type)
  : positionX(positionX),
    positionY(positionY),
    sizeX(sizeX),
    sizeY(sizeY),
    radius(0),
    mass(mass),
    gravity(gravity),
    type(type),
    isCollidingLeft(false),
    isCollidingRight(false),
    isCollidingTop(false),
    isCollidingBottom(false),
    forceX(0),
    forceY(0) {}

Box::Box(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity)
    : Body(positionX, positionY, sizeX, sizeY, mass, gravity, "Box") {

    applyForce(0, this->gravity);
}

Box::~Box() {}

void Box::update(std::vector<Body*> bodies, float gravity) {

    if (this->isDynamic) {

        this->isCollidingLeft = false;
        this->isCollidingRight = false;
        this->isCollidingTop = false;
        this->isCollidingBottom = false;

        this->positionX += this->forceX;

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

                        rect1 = {
                            this->positionX,
                            this->positionY,
                            this->sizeX,
                            this->sizeY
                        };

                        this->isCollidingLeft = boxCollideLeftBox(rect1, rect2);
                        this->isCollidingRight = boxCollideRightBox(rect1, rect2);

                        if (this->isCollidingBottom || this->isCollidingTop) {

                            float impulse = this->forceY / body->mass;

                            body->forceY += impulse;

                            this->forceY -= impulse;

                            continue;
                        }

                        if (this->isCollidingLeft || this->isCollidingRight) {

                            float impulse = this->forceX / body->mass;

                            body->forceX += impulse;

                            this->forceX -= impulse;
                        }
                    }
                }
            }
        }

        if (!this->isCollidingBottom && this->forceY != 0) {
            this->positionY += this->forceY;
        }
        else if (!this->isCollidingBottom && this->forceY == 0) {
            applyForce(0, this->gravity);
        }
        else {
            this->forceY = 0;
        }
    }
}

void Box::applyForce(float x, float y) {

    this->forceX += (this->mass * x) / 100;
    this->forceY += (this->mass * y) / 100;
}

Circle::Circle(float positionX, float positionY, float sizeX, float sizeY, float radius, float mass, float gravity)
    : Body(positionX, positionY, radius * 2, radius * 2, mass, gravity, "Circle") {

    this->radius = radius;
    applyForce(0, this->gravity);
}

Circle::~Circle() {}

void Circle::applyForce(float x, float y) {

    this->forceX += (this->mass * x) / 100;
    this->forceY += (this->mass * y) / 100;
}

void Circle::update(std::vector<Body*> bodies, float gravity) {

    if (this->isDynamic) {

        this->isCollidingLeft = false;
        this->isCollidingRight = false;
        this->isCollidingTop = false;
        this->isCollidingBottom = false;

        this->positionX += this->forceX;

        for (Body* body : bodies) {

            if (body != this) {

                if (body->type == "Box") {

                    float closestX = std::max(body->positionX, std::min(this->positionX, body->positionX + body->sizeX));
                    float closestY = std::max(body->positionY, std::min(this->positionY, body->positionY + body->sizeY));

                    float dx = this->positionX - closestX;
                    float dy = this->positionY - closestY;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance < this->radius) {

                        float overlap = this->radius - distance;

                        float nx = dx / distance;
                        float ny = dy / distance;

                        this->positionX += nx * overlap;
                        this->positionY += ny * overlap;

                        if (ny > 0) {
                            this->isCollidingTop = true;
                        }
                        if (ny < 0) {
                            this->isCollidingBottom = true;
                        }
                        if (nx > 0) {
                            this->isCollidingLeft = true;
                        }
                        if (nx < 0) {
                            this->isCollidingRight = true;
                        }

                        if (this->isCollidingTop || this->isCollidingBottom) {

                            float impulse = this->forceY / body->mass;

                            body->forceY += impulse;

                            this->forceY -= impulse / 2;
                        }
                        if (this->isCollidingLeft || this->isCollidingRight) {

                            float impulse = this->forceX / body->mass;

                            body->forceX += impulse;

                            this->forceX -= impulse / 2;
                        }
                    }
                }
                else if (body->type == "Circle") {

                    float dx = this->positionX - body->positionX;
                    float dy = this->positionY - body->positionY;
                    float distance = sqrt(dx * dx + dy * dy);
                    float sumRadius = this->radius + body->radius;

                    if (distance < sumRadius) {

                        float overlap = sumRadius - distance;

                        this->positionX += (dx / distance) * overlap;
                        this->positionY += (dy / distance) * overlap;

                        this->forceY = 0;
                    }
                }
            }
        }

        if (!this->isCollidingBottom) {

            if (this->forceY == 0) {
                applyForce(0, this->gravity);
            }
            this->positionY += this->forceY;
        }
        else {
            this->forceY = 0;
        }
    }
}