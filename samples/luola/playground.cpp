#include "playground.hpp"

#include "entity.hpp"
#include "shapes.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"
#include "components/ship_control.hpp"
#include "messages.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {
    addGameTypes(factory, global, false);
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
    physics.update(dt, entities);

    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);
    rendering.render(entities, projection);
}

void Playground::shutdown() {

}

void Playground::handleMessage(const Host::Packet& data) {
    Host::Packet::const_iterator it = data.begin();
    uint8_t type;
    deserialize(it, type);
    switch (type) {
    case CreateEntity:
        handleCreateEntity(it);
        break;
    }
}

void Playground::handleCreateEntity(Host::Packet::const_iterator& it) {
    std::string type;
    deserialize(it, type);
    factory.buildFromData(type, entities, it);
}
