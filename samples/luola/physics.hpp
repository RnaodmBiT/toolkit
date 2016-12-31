#pragma once
#include "global.hpp"

namespace {
    const Vec2f gravity = { 0, 100 };
}


bool bulletCollision(Ship& ship, Projectile& bullet);
