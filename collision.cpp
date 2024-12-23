#include "Collision.hpp"

bool boxCollideBox(const Rect& box1, const Rect& box2) {
    return box1.x < box2.x + box2.width &&
        box1.x + box1.width > box2.x &&
        box1.y < box2.y + box2.height &&
        box1.y + box1.height > box2.y;
}

bool boxCollideLeftBox(const Rect& box1, const Rect& box2) {
    return box1.x < box2.x + box2.width &&
        box1.x + box1.width > box2.x &&
        box1.y < box2.y + box2.height &&
        box1.y + box1.height > box2.y;
}

bool boxCollideRightBox(const Rect& box1, const Rect& box2) {
    return box1.x + box1.width > box2.x &&
        box1.x < box2.x + box2.width &&
        box1.y < box2.y + box2.height &&
        box1.y + box1.height > box2.y;
}

bool boxCollideTopBox(const Rect& box1, const Rect& box2) {
    return box1.y < box2.y + box2.height &&
        box1.y + box1.height > box2.y &&
        box1.x < box2.x + box2.width &&
        box1.x + box1.width > box2.x;
}

bool boxCollideBottomBox(const Rect& box1, const Rect& box2) {
    return box1.y + box1.height > box2.y &&
        box1.y < box2.y + box2.height &&
        box1.x < box2.x + box2.width &&
        box1.x + box1.width > box2.x;
}