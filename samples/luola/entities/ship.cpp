#include "ship.hpp"
#include "../shapes.hpp"
#include "../physics.hpp"

Ship::Ship(Global& global, const Vec2f& position, float rotation, Team team, uint8_t owner, Vec4f color) :
    global(global),
    drag(0.005f),
    mass(1),
    team(team),
    health(30),
    owner(owner) {

    state.position = position;
    state.rotation = rotation;

    shader = global.cache.get<Shader>("shader");
    playerName = Text(global.cache.get<Font>("font"),
                      shader, { 0, 0 }, "", 15);
}

void Ship::createGraphics() {
    Vec4f color = team == Red ? Vec4f{ 1, 0, 0, 1 } : Vec4f{ 0, 0, 1, 1 };
    shape = Shapes::createShipShape(color);
}

void Ship::setInput(const ShipInput& input) {
    state.input = input;
}

void Ship::setClientInput(const ShipInput& input) {
    clientInputs.emplace_back(global.time(), input);
}

void Ship::serverUpdate(float dt) {
    if (state.input.thrust) {
        thrust(500, dt);
    }
    if (state.input.keyboard) {
        if (state.input.left) {
            rotate(-4, dt);
        }
        if (state.input.right) {
            rotate(4, dt);
        }
    } else {
        float delta = wrapAngle(state.input.targetRotation - getRotation()) / dt;
        if (std::abs(delta) > 4) {
            delta = sign(delta) * 4;
        }
        rotate(delta, dt);
    }

    reloadTime -= dt;
    state.velocity += gravity * dt;
    state.position += state.velocity * dt;

    float force = state.velocity.lengthSquared() * drag;
    if (force > 0) {
        state.velocity -= state.velocity.normalized() * (force * dt / mass);
    }

    if (state.position.y > 0) {
        state.position.y = 0;
        state.velocity.y = 0;
    }
}

void Ship::clientUpdate(float dt) {
    state = clientTruth;
    float now = global.time();
    int input = 0;
    int counter = 0;
    for (float time = clientTruthTime + dt; time < now; time += dt) {
        if (input < clientInputs.size() && time >= clientInputs[input].first) {
            setInput(clientInputs[input++].second);
        }

        serverUpdate(dt);
        counter++;
    }

    tk_info(format("Client updated %% times", counter));
}

void Ship::draw(const Mat4f& projection) {
    shader->apply();

    Mat4f translation = translate(state.position.x, state.position.y, 0.0f);
    Mat4f spin = ::rotate(state.rotation, { 0, 0, 1 });

    shader->setUniform("transform", projection * translation * spin);
    shader->setUniform("tint", Vec4f{ 1, 1, 1, 1 });
    shader->clearTexture("image");
    shape.draw();

    Vec2f offset = -playerName.getSize() * 0.5f - Vec2f{ 0, 20 };
    playerName.draw(projection * translation, translate(offset.x, offset.y, 0.0f));
}

Vec2f Ship::getDirection() const {
    return{ std::cos(state.rotation), std::sin(state.rotation) };
}

float Ship::getRotation() const {
    return state.rotation;
}

Vec2f Ship::getPosition() const {
    return state.position;
}

Vec2f Ship::getVelocity() const {
    return state.velocity;
}

Team Ship::getTeam() const {
    return team;
}

uint8_t Ship::getOwner() const {
    return owner;
}

ShipInput Ship::getInput() const {
    return state.input;
}

void Ship::thrust(float strength, float dt) {
    state.velocity += getDirection() * (strength * dt / mass);
}

void Ship::takeDamage(int damage) {
    health -= damage;
}

void Ship::rotate(float speed, float dt) {
    state.rotation += speed * dt;
}

bool Ship::canShoot() const {
    return reloadTime <= 0;
}

void Ship::resetReloadTime() {
    reloadTime = 0.2f;
}

void Ship::setPlayerName(const std::string& name) {
    playerName.setText(name, 15);
}

int Ship::getHealth() const {
    return health;
}

void Ship::clearOldClientInputs() {
    clientTruthTime = global.time();
    while (clientInputs.size() && clientInputs[0].first < clientTruthTime) {
        clientInputs.erase(clientInputs.begin());
    }
}
