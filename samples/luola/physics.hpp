#pragma once
#include "global.hpp"

namespace {
    const Vec2f gravity = { 0, 200 };
}


inline int bullet_collision(Ship* ship, Projectile* bullet, float dt) {
    Vec2f delta = bullet->getPosition() - ship->getPosition();
    if (delta.length() < 9.0f) {
        return 1;
    }
    return 0;
}