#include "playground.hpp"
#include "shapes.hpp"
#include "messages.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) :
    GameState(global),
    playerInputTimer(30),
    ships(global),
    projectiles(global) {
    client.connect(global.remote, 2514, { "Player" });
    space_state = false;
    mouse_mode = false;
    client.onMessageReceived.attach(onMessageReceived, [this](const Host::Packet& data) {
        handleMessage(data);
    });
}

GameState* Playground::update(float dt) {
    if (global.server) {
        global.server->update(dt);
    }
    client.pollEvents();

    ships.update(dt);
    projectiles.update(dt);

    while (playerInputTimer.update()) {
        handlePlayerInput();
    }

    return GameState::update(dt);
}

void Playground::draw() {
    PlayerInfo* info = client.getPlayer();
    if (info) {
        Ship* ship = ships.get(info->ship);
        if (ship) {
            screen_position = (screen_position * 0.7f) + (ship->getPosition() + (ship->getVelocity() * 0.5f)) * 0.3f;
        }
    }
    Mat4f projection = orthographic(screen_position.x - (float)global.width / 2, screen_position.y - (float)global.height / 2, (float)global.width / 2 + screen_position.x, (float)global.height / 2 + screen_position.y);
    ships.render(projection);
    projectiles.render(projection);
}

void Playground::shutdown() {
    client.disconnect();
    if (global.server) {
        global.server.reset();
    }
}

void Playground::handleMessage(const Host::Packet& data) {
    Host::Packet::const_iterator it = data.begin();
    uint8_t type;
    deserialize(it, type);
    switch (type) {
    case ShipUpdate:
        handleShipUpdate(it);
        break;
    case ProjectileUpdate:
        handleProjectileUpdate(it);
        break;
    }
}

void Playground::handleShipUpdate(Host::Packet::const_iterator& it) {
    deserialize(it, ships);
}

void Playground::handleProjectileUpdate(Host::Packet::const_iterator& it) {
    deserialize(it, projectiles);
}

void Playground::handlePlayerInput() {
    PlayerInfo* info = client.getPlayer();
    if (!info) {
        return;
    }
    Ship* ship = ships.get(info->ship);
    if (!ship) {
        return;
    }

    ShipInput input;
    input.thrust = global.input.isKeyDown(SDLK_w);
    input.shoot = global.input.isButtonDown(SDL_BUTTON_LEFT);
    Vec2f ship_screen_pos = Vec2f{ (float)global.width / 2, (float)global.height / 2 } -ship->getVelocity() * 0.5f;
    input.target_rotation = std::atan2((float)global.input.getMousePosition().y - ship_screen_pos.y, (float)global.input.getMousePosition().x - ship_screen_pos.x);
    input.left = global.input.isKeyDown(SDLK_a);
    input.right = global.input.isKeyDown(SDLK_d);

    if (global.input.isKeyDown(SDLK_SPACE) && space_state == false) {
        mouse_mode = !mouse_mode;
    }
    input.mode = mouse_mode;
    space_state = global.input.isKeyDown(SDLK_SPACE);

    client.send(false, (uint8_t)PlayerInput, input);
}
