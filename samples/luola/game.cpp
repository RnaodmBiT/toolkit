#include "game.hpp"
#include "messages.hpp"
#include <SDL.h>

Game::Game(Global& global) : LuolaState(global) {
    Font* font = global.resources.get<Font>("font");
    Shader* shader = global.resources.get<Shader>("shader");

    createShipShape();

    scene.reset(new DrawableNode("scene"));
    scene->setShader(shader);

    clientOnMessageReceived.event = [&] (const Host::Packet& packet) {
        Host::Packet::const_iterator it = packet.begin();
        uint8_t type;
        deserialize(it, type);

        switch (type) {
        case LuolaMessage::UpdateShips:
            updateShips(it);
            break;
        case LuolaMessage::DeleteShip:
            tk_info("Received delete ship command");
            break;
        }
    };

    global.client.onMessageReceived.attach(clientOnMessageReceived);
}

void Game::shutdown() {
    global.client.disconnect();
}

LuolaState* Game::update(float dt) {
    global.server.update(dt);
    global.client.pollEvents();

    for (auto& ship : ships) {
        ship.update(0);
    }

    return LuolaState::update(dt);
}

void Game::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global.resolution.x, (float)global.resolution.y);
    scene->draw(projection);
}

void Game::updateShips(Host::Packet::const_iterator msg) {
    int count;
    deserialize(msg, count);
    for (int i = 0; i < count; ++i) {
        int id;
        Vec2f position;
        float angle;
        deserialize(msg, id, position, angle);

        auto it = std::find_if(ships.begin(), ships.end(), [&] (const Ship& ship) {
            return ship.getID() == id;
        });

        if (it != ships.end()) {
            it->setPosition(position);
            it->setAngle(angle);
        } else {
            ShapeNode* node = new ShapeNode("player", shapeShip);
            scene->addChild(node);
            ships.emplace_back(id, position, Vec4f{ 0, 0, 1, 1 }, node);
        }
    }
}

void Game::createShipShape() {
    Vec2f points[] = {
        { 10, 0 },
        { -5, 7.5f },
        { -2.5f, 0 },

        { 10, 0 },
        { -2.5f, 0 },
        { -5, -7.5f }
    };

    Vec4f colors[] = {
        { 1, 1, 1, 1 },{ 1, 1, 1, 1 },{ 1, 1, 1, 1 },
        { 1, 1, 1, 1 },{ 1, 1, 1, 1 },{ 1, 1, 1, 1 },
    };

    Vec2f uvs[] = {
        { 0, 0 },{ 0, 0 },{ 0, 0 },
        { 0, 0 },{ 0, 0 },{ 0, 0 },
    };

    shapeShip = Shape::polygon(points, colors, uvs, sizeof_array(points));
}
