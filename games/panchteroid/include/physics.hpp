#pragma once
#include "vec2.hpp"

struct Nave {
    vec2 head;
    vec2 vel;
    float angle;

    void update(bool acc, bool right, bool left, float dt);
};