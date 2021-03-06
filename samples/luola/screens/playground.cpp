#include "playground.hpp"
#include "../shapes.hpp"
#include "../messages.hpp"
#include "title.hpp"
#include "../menu/cursor.hpp"

Playground::Playground(Global& global) :
    GameState(global),
    playerInputTimer(30),
    ships(global),
    projectiles(global),
    background(global) {

    Cursor::set(Cursor::Crosshair);
    global.client->onMessageReceived.attach(onMessageReceived, [this] (const Host::Packet& data) {
        handleMessage(data);
    });

    if (!global.server) {
        global.client->onServerDisconnected.attach(onDisconnectedFromServer, [&] () {
            setNextState(new Title(global));
        });
    }

    global.input.onKeyDown.attach(onKeyDown, [&] (int key) {
        if (key == SDLK_ESCAPE) {
            setNextState(new Title(global));
        } else if (key == SDLK_SPACE) {
            playerInput.keyboard = !playerInput.keyboard;
        }
    });

    camera.size = Vec2f{ (float)global.width, (float)global.height };
}

GameState* Playground::update(float dt) {
    global.updateNetwork(dt);

    ships.update(dt);

    projectiles.update(dt);
    projectiles.checkCollisions(ships);

    while (playerInputTimer.update()) {
        handlePlayerInput();
    }

    updateCamera(dt);
    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f screen = orthographic(0, 0, (float)global.width, (float)global.height);
    Mat4f projection = camera.projection();

    background.draw(screen, camera.position);

    ships.draw(projection);
    projectiles.draw(projection);
}

void Playground::shutdown() {
    global.client->disconnect();
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

    for (auto& idShip : ships) {
        Ship& ship = idShip.second;
        int owner = ship.getOwner();
        PlayerInfo* player = global.client->getPlayer(owner);
        if (owner >= 0 && player) {
            ship.setPlayerName(player->name);
        }
    }
}

void Playground::handleProjectileUpdate(Host::Packet::const_iterator& it) {
    deserialize(it, projectiles);
}

void Playground::handlePlayerInput() {
    PlayerInfo* info = global.client->getPlayer();
    if (!info) {
        return;
    }
    Ship* ship = ships.get(info->ship);
    if (!ship) {
        return;
    }

    playerInput.thrust = global.input.isKeyDown(SDLK_w);
    playerInput.left = global.input.isKeyDown(SDLK_a);
    playerInput.right = global.input.isKeyDown(SDLK_d);
    playerInput.shoot = global.input.isButtonDown(SDL_BUTTON_LEFT);

    Vec2f mousePosition = camera.screenToWorld(global, { (float)global.input.getMousePosition().x, (float)global.input.getMousePosition().y });
    playerInput.targetRotation = angleBetween(mousePosition, ship->getPosition());

    global.client->send(false, (uint8_t)PlayerInput, playerInput);
}

void Playground::updateCamera(float dt) {
    PlayerInfo* player = global.client->getPlayer();
    if (player) {
        Ship* ship = ships.get(player->ship);
        if (ship) {
            camera.lerpTo(ship->getPosition() + ship->getVelocity() * 0.5f, 0.99f, dt);
        }
    }
}
