#include "playground.hpp"
#include "../shapes.hpp"
#include "../messages.hpp"
#include "title.hpp"
#include "../menu/cursor.hpp"

Playground::Playground(Global& global) :
    GameState(global),
    playerInputTimer(30),
    gameUpdateTimer((float)global.tickRate),
    background(global) {

    shader = global.cache.get<Shader>("shader");
    shipShape = Shapes::createShipShape({ 1, 1, 1, 1 });

    clientTick = previousTick = latestServerTick = 0;

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

    while (playerInputTimer.update()) {
        handlePlayerInput();
    }

    while (gameUpdateTimer.update()) {
        previousTick = clientTick;
        if (clientTick < latestServerTick - 2) {
            clientTick += 2;
        } else if (clientTick < latestServerTick) {
            clientTick++;
        }

        tk_info(format("Client %%, Previous %%, Server %%", clientTick, previousTick, latestServerTick));
    }

    updateCamera(dt);
    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f screen = orthographic(0, 0, (float)global.width, (float)global.height);
    Mat4f projection = camera.projection();

    background.draw(screen, camera.position);

    for (auto& pair : ships) {
        ClientShip& ship = pair.second;

        int start = 0, end = 0;
        for (int i = 0; i < ship.history.size(); ++i) {
            if (ship.history[i].tick <= previousTick) {
                start = i;
            }
            if (ship.history[i].tick <= clientTick) {
                end = i;
            }
        }

        float interpolation = 0.0f;
        if (start != end) {
            interpolation = gameUpdateTimer.progress() / gameUpdateTimer.period();
        }

        Vec2f position = lerp(ship.history[start].position, ship.history[end].position, interpolation);
        float rotation = lerp(ship.history[start].rotation, ship.history[end].rotation, interpolation);

        shader->apply();
        shader->clearTexture("image");
        shader->setUniform("tint", Vec4f{ 1, 1, 1, 1 });
        shader->setUniform("transform", projection * translate(position.x, position.y, 0.0f) * rotate(rotation, { 0, 0, 1 }));
        shipShape.draw();

        ship.render = { 0, position, rotation };
    }
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
    case GameUpdate:
        handleGameUpdate(it);
        break;
    }
}

void Playground::handleGameUpdate(Host::Packet::const_iterator& it) {
    deserialize(it, latestServerTick);

    if (clientTick == previousTick && previousTick == 0) {
        clientTick = previousTick = latestServerTick;
    }

    int shipCount;
    deserialize(it, shipCount);

    std::unordered_set<int> receivedShips;

    for (int i = 0; i < shipCount; ++i) {
        int id;
        deserialize(it, id);
        receivedShips.insert(id);

        ships[id].history.push_back({ latestServerTick });
        ShipState& state = ships[id].history.back();

        deserialize(it, state.position, state.rotation);

        while (ships[i].history.size() && ships[i].history.front().tick < previousTick) {
            ships[i].history.erase(ships[i].history.begin());
        }
    }

    for (auto it = ships.begin(); it != ships.end(); ) {
        if (receivedShips.count(it->first) == 0) {
            it = ships.erase(it);
        } else {
            ++it;
        }
    }
}

void Playground::handlePlayerInput() {
    PlayerInfo* info = global.client->getPlayer();
    if (!info || ships.count(info->ship) == 0) {
        return;
    }

    ShipState& ship = ships.at(info->ship).render;

    playerInput.thrust = global.input.isKeyDown(SDLK_w);
    playerInput.left = global.input.isKeyDown(SDLK_a);
    playerInput.right = global.input.isKeyDown(SDLK_d);
    playerInput.shoot = global.input.isButtonDown(SDL_BUTTON_LEFT);

    Vec2f mousePosition = camera.screenToWorld(global, { (float)global.input.getMousePosition().x, (float)global.input.getMousePosition().y });
    playerInput.targetRotation = angleBetween(mousePosition, ship.position);

    global.client->send(false, (uint8_t)PlayerInput, playerInput);
}

void Playground::updateCamera(float dt) {
    PlayerInfo* player = global.client->getPlayer();
    if (player && ships.count(player->ship)) {
        ShipState& ship = ships.at(player->ship).render;
        camera.lerpTo(ship.position, 0.99f, dt);
    }
}
