#include "game_server.hpp"
#include "messages.hpp"
#include "global.hpp"

GameServer::GameServer(Global& global) : 
    global(global), 
    updateTimer(20),
    ships(global),
    projectiles(global) {
    server.start(2514);
    
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

GameServer::~GameServer() {
    server.disconnect();
}

void GameServer::update(float dt) {
    server.pollEvents();

    ships.update(dt);
    projectiles.update(dt);

    shootBullets();
    
    while (updateTimer.update()) {
        // Broadcast the game state to all clients
        server.broadcast(false, (uint8_t)ShipUpdate, ships);
        server.broadcast(false, (uint8_t)ProjectileUpdate, projectiles);
    }
}

void GameServer::handleMessage(int id, const Host::Packet& data) {
    Host::Packet::const_iterator it = data.begin();
    uint8_t type;
    deserialize(it, type);
    switch (type) {
    case PlayerInput:
        handlePlayerInput(id, it);
        break;
    }
}

void GameServer::handlePlayerConnect(int id) {
    Team playerTeam = getAppropriateTeam();

    int ship = ships.spawn(id, { 0, -400 }, -pi / 2, playerTeam);
    PlayerInfo* player = server.getPlayer(id);
    player->ship = ship;
    player->team = playerTeam;
    server.updatePlayerTable(); // this pushes the updates player info to all players
}

void GameServer::handlePlayerDisconnect(int id) {

}

void GameServer::handlePlayerInput(int id, Host::Packet::const_iterator& it) {
    PlayerInfo* player = server.getPlayer(id);
    tk_assert(player, "Invalid player ID received from client");
    Ship* ship = ships.get(player->ship);
    if (ship) {
        ShipInput input;
        deserialize(it, input);
        ship->setInput(input);
    }
}

void GameServer::shootBullets() {
    for (auto& pair : ships) {
        Ship& ship = pair.second;
        if (ship.getInput().shoot && ship.canShoot()) {
            ship.resetReloadTime();

            projectiles.spawn(ship.getPosition(), ship.getVelocity(), ship.getRotation());
        }
    }
}

Team GameServer::getAppropriateTeam() {
    int red = 0, blue = 0;
    for (int player : server.getPlayerIDs()) {
        PlayerInfo* info = server.getPlayer(player);
        if (info->team == Red) {
            red++;
        } else {
            blue++;
        }
    }

    return blue <= red ? Blue : Red;
}
