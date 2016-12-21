#pragma once
#include "global.hpp"

struct Camera {
    Vec2f position, size;

    void lerpTo(const Vec2f& newPosition, float rate, float dt) {
        position = lerp(position, newPosition, 1 - std::pow(1 - rate, dt));
    }

    Mat4f projection() {
        return orthographic(position.x - size.x / 2, position.y - size.y / 2,
                            position.x + size.x / 2, position.y + size.y / 2);
    }

    Vec2f screenToWorld(const Global& global, const Vec2f& screen) const {
        Vec2f world;
        world.x = lerp(position.x - size.x / 2, position.x + size.x / 2, screen.x / (float)global.width);
        world.y = lerp(position.y - size.y / 2, position.y + size.y / 2, screen.y / (float)global.height);
        return world;
    }
};