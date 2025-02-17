#pragma once

#ifndef BODY_HPP
#define BODY_HPP

#include <string>
#include <vector>

class Body {

    public:

        Body(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity, std::string type);

        virtual ~Body() = default;

        virtual void update(std::vector<Body*> bodies, float gravity) = 0;

        void setDynamic(bool dynamic) {
            isDynamic = dynamic;
        };

        std::string type;

        float positionX;
        float positionY;
        float sizeX;
        float sizeY;
        
        float radius;

        float mass;

        float gravity;

        float forceX;
        float forceY;

        bool isDynamic = false;
        bool isCollidingLeft;
        bool isCollidingRight;
        bool isCollidingTop;
        bool isCollidingBottom;

};

class Box : public Body {

    public:

        Box(float positionX, float positionY, float sizeX, float sizeY, float mass, float gravity);
        ~Box() override;

        void update(std::vector<Body*> bodies, float gravity);

        void applyForce(float x, float y);

};

class Circle : public Body {

    public:

        Circle(float positionX, float positionY, float sizeX, float sizeY, float radius, float mass, float gravity);
        ~Circle() override;

        void update(std::vector<Body*> bodies, float gravity);

        void applyForce(float x, float y);

};

#endif