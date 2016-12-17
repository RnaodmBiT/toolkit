#include "game_server.hpp"
#include "messages.hpp"
#include "global.hpp"

GameServer::GameServer(Global& global) : 
    global(global), 
    updateTimer(30),
    ships(global) {
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
    ships.update(dt);

    while (updateTimer.update()) {
        // Broadcast the game state to all clients
        server.broadcast(false, (uint8_t)ShipUpdate, ships);
    }
}

void GameServer::handleMessage(int id, const Host::Packet& data) {
}

void GameServer::handlePlayerConnect(int id) {
    int ship = ships.spawn({ (float)global.width / 2, 100 }, -pi / 2);
    PlayerInfo* player = server.getPlayer(id);
    player->ship = ship;
    server.updatePlayerTable(); // this pushes the updates player info to all players
}

void GameServer::handlePlayerDisconnect(int id) {

}