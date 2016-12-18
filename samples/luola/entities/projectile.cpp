#include "projectile.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Projectile::Projectile(Global& global, const Vec2f& position, const Vec2f& shipVelocity, float rotation) :
    position(position),
    velocity(shipVelocity),
    drag(0.001f),
    mass(1),
    shape(Shapes::createBulletShape({ 1, 1, 1, 1 })) {
    shader = global.cache.get<Shader>("shader");
    velocity += Vec2f{ std::cos(rotation), std::sin(rotation) } *500.0f;
}

void Projectile::update(float dt) {
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
}

void Projectile::draw(const Mat4f& projection) {
    shader->apply();
    shader->setUniform("transform", projection * getTransform());
    shape.draw();
}

Mat4f Projectile::getTransform() const {
    float rotation = std::atan2(velocity.y, velocity.x);
    return translate(position.x, position.y, 0.0f) * ::rotate(rotation, { 0, 0, 1 });
}
