#include "ship.hpp"

Ship::Ship() { }

Ship::Ship(Vec2f position, ShapeNode* shape, Vec4f color) : 
    position(position),
    angle(pi / 2),
    shape(shape) {
    shape->setTint(color);
}

void Ship::update(float dt) {
    updateTransform();
}

void Ship::updateTransform() {
    auto m = translate(position.x, position.y, 0.0f) * rotate(angle, { 0.0f, 0.0f, -1.0f });
    shape->setTransform(m);
}