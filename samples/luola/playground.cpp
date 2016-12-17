#include "playground.hpp"
#include "shapes.hpp"
#include "messages.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : 
    GameState(global),
    ships(global) {
    client.connect(global.remote, 25140, { "Player" });

    client.onMessageReceived.attach(onMessageReceived, [this] (const Host::Packet& data) {
        handleMessage(data);
    });
}

GameState* Playground::update(float dt) {
    if (global.server) {
        global.server->update(dt);
    }
    client.pollEvents();

    // ships.update(dt); // NETWORK TEST

    handlePlayerInput();

    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);
    ships.render(projection);
}

void Playground::shutdown() {

}

void Playground::handleMessage(const Host::Packet& data) {
    Host::Packet::const_iterator it = data.begin();
    uint8_t type;
    deserialize(it, type);
    switch (type) {
    case ShipUpdate:
        handleShipUpdate(it);
        break;
    }
}

void Playground::handleShipUpdate(Host::Packet::const_iterator& it) {
    deserialize(it, ships);
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
    input.left = global.input.isKeyDown(SDLK_a);
    input.right = global.input.isKeyDown(SDLK_d);

    client.send(false, (uint8_t)PlayerInput, input);
}
