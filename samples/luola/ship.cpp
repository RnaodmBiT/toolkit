#include "ship.hpp"

namespace {
    const Vec2f gravity = Vec2f{ 0.0f, 200.0f };
    const float drag = 0.005f;
    const float mass = 1.0f;
}

Ship::Ship() { }

Ship::Ship(int id, Vec2f position, Vec4f color, ShapeNode* shape) :
    id(id),
    position(position),
    angle(-pi / 2),
    shape(shape) {
    if (shape) {
        shape->setTint(color);
    }
}

Ship::~Ship() { }

void Ship::update(float dt) {
    velocity += gravity * dt;
    position += velocity * dt;

    float force = velocity.lengthSquared() * drag;
    if (force > 0) {
        velocity -= velocity.normalized() * (force * dt / mass);
    }

    if (position.y > 500) {
        position.y = 500;
        velocity.y = 0;
    }

    updateTransform();
}

void Ship::updateTransform() {
    if (shape) {
        auto m = translate(position.x, position.y, 0.0f) * ::rotate(angle, { 0.0f, 0.0f, 1.0f });
        shape->setTransform(m);
    }
}

Vec2f Ship::getDirection() const {
    return{ std::cos(angle), std::sin(angle) };
}

Vec2f Ship::getPosition() const {
    return position;
}

float Ship::getAngle() const {
    return angle;
}

void Ship::setPosition(const Vec2f& p) {
    position = p;
}

void Ship::setAngle(float a) {
    angle = a;
}

ShapeNode* Ship::getNode() const {
    return shape.get();
}

int Ship::getID() const {
    return id;
}

void Ship::applyThrust(float strength, float dt) {
    velocity += getDirection() * (strength * dt / mass);
}

void Ship::rotate(float speed, float dt) {
    angle += speed * dt;
}