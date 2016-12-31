#include "ship.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Ship::Ship(Global& global, const Vec2f& position, float rotation, Team team, uint8_t owner, Vec4f color) :
    position(position),
    rotation(rotation),
    drag(0.005f),
    mass(1),
    team(team),
    health(30),
    owner(owner) {

    shader = global.cache.get<Shader>("shader");
    playerName = Text(global.cache.get<Font>("font"),
                      shader, { 0, 0 }, "", 15);
}

void Ship::createGraphics() {
    Vec4f color = team == Red ? Vec4f{ 1, 0, 0, 1 } : Vec4f{ 0, 0, 1, 1 };
    shape = Shapes::createShipShape(color);
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

    if (position.y > 0) {
        position.y = 0;
        velocity.y = 0;
    }
}

void Ship::draw(const Mat4f& projection) {
    shader->apply();

    Mat4f translation = translate(position.x, position.y, 0.0f);
    Mat4f spin = ::rotate(rotation, { 0, 0, 1 });

    shader->setUniform("transform", projection * translation * spin);
    shader->setUniform("tint", Vec4f{ 1, 1, 1, 1 });
    shader->clearTexture("image");
    shape.draw();

    Vec2f offset = -playerName.getSize() * 0.5f - Vec2f{ 0, 20 };
    playerName.draw(projection * translation, translate(offset.x, offset.y, 0.0f));
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

Team Ship::getTeam() const {
    return team;
}

uint8_t Ship::getOwner() const {
    return owner;
}

ShipInput Ship::getInput() const {
    return input;
}

void Ship::thrust(float strength, float dt) {
    velocity += getDirection() * (strength * dt / mass);
}

void Ship::takeDamage(int damage) {
    health -= damage;
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

void Ship::setPlayerName(const std::string& name) {
    playerName.setText(name, 15);
}

int Ship::getHealth() const {
    return health;
}
