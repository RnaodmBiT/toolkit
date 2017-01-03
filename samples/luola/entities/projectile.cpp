#include "projectile.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Projectile::Projectile(Global& global, const Vec2f& position, const Vec2f& shipVelocity, float rotation, int type) :
    position(position + Vec2f{ std::cos(rotation), std::sin(rotation) } * 5.0f),
    velocity(shipVelocity),
    drag(0.001f),
    type(type),
    rotation(rotation),
    mass(projectileTypes[type].mass),
    targetShipId(-1),
    shape(Shapes::createBulletShape({ 1, 1, 1, 1 })) {
    shader = global.cache.get<Shader>("shader");
    velocity += Vec2f{ std::cos(rotation), std::sin(rotation) } * 600.0f;
}

void Projectile::update(float dt, ShipManager& ships) {
    velocity += gravity * dt;
    position += velocity * dt;

    float drag_force = velocity.lengthSquared() * drag;
    if (drag_force > 0) {
        velocity -= velocity.normalized() * (drag_force * dt / mass);
    }
    

    if (projectileTypes[type].tracking && targetShipId != -1 && ships.get(targetShipId)) {
        Vec2f deltap = ships.get(targetShipId)->getPosition() - position;
        Vec2f deltav = ships.get(targetShipId)->getVelocity() - velocity;
        Vec2f left = Vec2f{ deltap.y , -deltap.x }.normalized();
        float shift = left.dot(deltav);
        deltap += left * shift;
        float deltar = (std::atan2(deltap.y, deltap.x) - rotation) * 9.0f;
        if (std::abs(deltar) > 40) {
            deltar = sign(deltar) * 40;
        }
        rotate_projectile(deltar, dt);
        velocity += Vec2f{ cosf(rotation) , sinf(rotation) } * 700.0f * dt / mass;

    }
    else {
        rotation = std::atan2(velocity.y, velocity.x);
    }

    if (position.y > 0) {
        position.y = 0;
        if (!projectileTypes[type].tracking) {
            velocity.y = 0;
        }
    }
}

void Projectile::rotate_projectile(float speed, float dt) {
    rotation += speed * dt;
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

void Projectile::setTarget(int id) {
    targetShipId = id;
}

Vec2f Projectile::getVelocity() {
    return velocity;
}

int Projectile::getType() {
    return type;
}