#pragma once
#include <core.hpp>
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

class Ship {
    std::unique_ptr<ShapeNode> shape;

    Vec2f position, velocity;
    float angle;
    int id;

    void updateTransform();

public:
    Ship();
    Ship(int player, Vec2f position, Vec4f color, ShapeNode* shape);
    ~Ship();

    Ship(Ship&& move) {
        *this = std::move(move);
    }

    void operator=(Ship&& move) {
        std::swap(shape, move.shape);
        std::swap(position, move.position);
        std::swap(velocity, move.velocity);
        std::swap(angle, move.angle);
        std::swap(id, move.id);
    }

    void update(float dt);

    Vec2f getDirection() const;
    Vec2f getPosition() const;
    float getAngle() const;

    void setPosition(const Vec2f&);
    void setAngle(float angle);

    ShapeNode* getNode() const;
    int getID() const;

    void applyThrust(float thrust, float dt);
    void rotate(float speed, float dt);
};
