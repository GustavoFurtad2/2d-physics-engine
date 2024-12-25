#pragma once

struct Rect {
    float x, y;
    float width, height;
    float r, g, b;
    float scale;
};

bool boxCollideBox(const Rect& box1, const Rect& box2);
bool boxCollideLeftBox(const Rect& box1, const Rect& box2);
bool boxCollideRightBox(const Rect& box1, const Rect& box2);
bool boxCollideTopBox(const Rect& box1, const Rect& box2);
bool boxCollideBottomBox(const Rect& box1, const Rect& box2);
