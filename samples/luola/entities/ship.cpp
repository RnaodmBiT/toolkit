#include "ship.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Ship::Ship(Global& global, const Vec2f& position, float rotation, int team, Vec4f color) :
    position(position),
    rotation(rotation),
    drag(0.005f),
    mass(1),
    team(team),
    shape(Shapes::createShipShape(color)) {
    shader = global.cache.get<Shader>("shader");
}

void Ship::setInput(const ShipInput& shipInput) {
    input = shipInput;
}

void Ship::update(float dt) {
    if (input.thrust) {
        thrust(500, dt);
    }
    if (input.keyboard) {
        if (input.left) {
            rotate(-4, dt);
        }
        if (input.right) {
            rotate(4, dt);
        }
    }
    else {
        float delta = wrapAngle(input.targetRotation - getRotation()) / dt;
        if (std::abs(delta) > 4) {
            delta = sign(delta) * 4;
        }
        rotate(delta, dt);
    }

    reloadTime -= dt;
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

void Ship::draw(const Mat4f& projection) {
    shader->apply();
    shader->setUniform("transform", projection * getTransform());
    shape.draw();
}

Mat4f Ship::getTransform() const {
    return translate(position.x, position.y, 0.0f) * ::rotate(rotation, { 0, 0, 1 });
}

Vec2f Ship::getDirection() const {
    return{ std::cos(rotation), std::sin(rotation) };
}

float Ship::getRotation() const {
    return rotation;
}

Vec2f Ship::getPosition() const {
    return position;
}

Vec2f Ship::getVelocity() const {
    return velocity;
}

int Ship::getTeam() const {
    return team;
}

ShipInput Ship::getInput() const {
    return input;
}

void Ship::thrust(float strength, float dt) {
    velocity += getDirection() * (strength * dt / mass);
}

void Ship::rotate(float speed, float dt) {
    rotation += speed * dt;
}

bool Ship::canShoot() const {
    return reloadTime <= 0;
}

void Ship::resetReloadTime() {
    reloadTime = 0.2f; // 5 Hz
}
