#include "game_server.hpp"
#include "types.hpp"
#include "messages.hpp"
#include "global.hpp"

GameServer::GameServer(Global& global) : global(global) {
    addGameTypes(factory, global, true);

    server.start(25140);
    
    server.onMessageReceived.attach(onMessageReceived, [this] (int id, const Host::Packet& data) {
        handleMessage(id, data);
    });

    server.onPlayerConnected.attach(onPlayerConnected, [this](int id) {
        handlePlayerConnect(id);
    });

    server.onPlayerDisconnected.attach(onPlayerDisconnected, [this](int id) {
        handlePlayerDisconnect(id);
    });
}

void GameServer::update(float dt) {
    server.pollEvents();
    physics.update(dt, entities);
}

void GameServer::handleMessage(int id, const Host::Packet& data) {

}

void GameServer::handlePlayerConnect(int id) {
    int entity = entities.getFreeID();
    Vec2f position = { (float)global.width / 2, (float)global.height / 2 };
    Vec4f color = { 0, 0, 1, 1 };

    factory.build("ship", entities, entity, position, color);
    server.broadcast(true, (uint8_t)CreateEntity, std::string("ship"), entity, position, color);
}

void GameServer::handlePlayerDisconnect(int id) {

}