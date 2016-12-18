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

    client.onMessageReceived.attach(onMessageReceived, [this] (const Host::Packet& data) {
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
	static float shiftx = 0;
	static float shifty = 0;
	PlayerInfo* info = client.getPlayer();
	if (info) {
		Ship* ship = ships.get(info->ship);
		if (ship) {
			shiftx = (shiftx * 0.7f) + 0.3f * (ship->getPosition().x + ship->getVelocity().x / 2);
			shifty = (shifty * 0.7f) + 0.3f * (ship->getPosition().y + ship->getVelocity().y / 2);
		}
	}
	Mat4f projection = orthographic(shiftx - (float)global.width/2, shifty - (float)global.height/2, (float)global.width/2+shiftx, (float)global.height/2+shifty);
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
    input.left = global.input.isKeyDown(SDLK_a);
    input.right = global.input.isKeyDown(SDLK_d);
    input.shoot = global.input.isButtonDown(SDL_BUTTON_LEFT);

    client.send(false, (uint8_t)PlayerInput, input);
}
