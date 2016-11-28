#pragma once
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

class Ship {
    std::unique_ptr<ShapeNode> shape;

    Vec2f position, velocity;
    float angle;

    void updateTransform();

public:
    Ship();
    Ship(Vec2f position, ShapeNode* shape, Vec4f color);

    void update(float dt);

    Vec2f getDirection() const;
    Vec2f getPosition() const;
    float getAngle() const;

    void applyThrust(float thrust, float dt);
    void rotate(float speed, float dt);
};
