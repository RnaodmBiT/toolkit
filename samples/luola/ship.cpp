#include "ship.hpp"

namespace {
    const Vec2f gravity = Vec2f{ 0.0f, 200.0f };
    const float drag = 0.005f;
    const float mass = 1.0f;
}

Ship::Ship() { }

Ship::Ship(Vec2f position, ShapeNode* shape, Vec4f color) : 
    position(position),
    angle(pi / 2),
    shape(shape) {
    shape->setTint(color);
}

void Ship::update(float dt) {
    velocity += gravity * dt;
    position += velocity * dt;

    float force = velocity.lengthSquared() * drag;
    velocity -= velocity.normalized() * (force * dt / mass);

    updateTransform();
}

void Ship::updateTransform() {
    auto m = translate(position.x, position.y, 0.0f) * ::rotate(angle, { 0.0f, 0.0f, -1.0f });
    shape->setTransform(m);
}

Vec2f Ship::getDirection() const {
    return{ std::cos(angle), -std::sin(angle) };
}

void Ship::applyThrust(float strength, float dt) {
    velocity += getDirection() * (strength * dt / mass);
}

void Ship::rotate(float speed, float dt) {
    angle += speed * dt;
}