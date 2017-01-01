#include "projectile.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Projectile::Projectile(Global& global, const Vec2f& position, const Vec2f& shipVelocity, float rotation, int type) :
    position(position + Vec2f{ std::cos(rotation), std::sin(rotation) } * 4.0f),
    velocity(shipVelocity),
    drag(0.001f),
    type(type),
    mass(projectileTypes[type].mass),
    shape(Shapes::createBulletShape({ 1, 1, 1, 1 })) {
    shader = global.cache.get<Shader>("shader");
    velocity += Vec2f{ std::cos(rotation), std::sin(rotation) } *500.0f;
}

void Projectile::update(float dt) {
    velocity += gravity * dt;
    position += velocity * dt;

    float drag_force = velocity.lengthSquared() * drag;
    if (drag_force > 0) {
        velocity -= velocity.normalized() * (drag_force * dt / mass);
    }
    rotation = std::atan2(velocity.y, velocity.x);


    if (position.y > 0) {
        position.y = 0;
        velocity.y = 0;
    }
}

void Projectile::draw(const Mat4f& projection) {
    shader->apply();
    shader->setUniform("transform", projection * getTransform());
    shader->setUniform("tint", projectileTypes[type].color);
    shader->clearTexture("image");
    shape.draw();
}

Mat4f Projectile::getTransform() const {
    return translate(position.x, position.y, 0.0f) * ::rotate(rotation, { 0, 0, 1 });
}

Vec2f Projectile::getPosition() {
    return position;
}

Vec2f Projectile::getVelocity() {
    return velocity;
}

int Projectile::getType() {
    return type;
}