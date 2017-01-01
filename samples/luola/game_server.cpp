#include "game_server.hpp"
#include "messages.hpp"
#include "global.hpp"
#include "physics.hpp"

GameServer::GameServer(Global& global) : 
    global(global), 
    updateTimer(10),
    ships(global),
    projectiles(global),
    inProgress(false) {

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

    ships.serverUpdate(dt);

    projectiles.update(dt);
    projectiles.checkCollisions(ships);

    ships.checkHealth();

    shootBullets();

    while (updateTimer.update()) {
        server.broadcast(false, (uint8_t)ShipUpdate, ships);
        server.broadcast(false, (uint8_t)ProjectileUpdate, projectiles);
    }
}

void GameServer::startGame() {
    inProgress = true;

    for (int player : server.getPlayerIDs()) {
        Vec2f position = { random(-1000, 1000), random(-1000, 0) };
        spawnShip(player, position);
    }

    server.broadcast(true, (uint8_t)StartGame);
}

void GameServer::handleMessage(int id, const Host::Packet& data) {
    Host::Packet::const_iterator it = data.begin();
    uint8_t type;
    deserialize(it, type);
    switch (type) {
    case PlayerInput:
        handlePlayerInput(id, it);
        break;
    case PlayerChangeTeam:
        handlePlayerChangeTeam(id);
        break;
    }
}

void GameServer::handlePlayerConnect(int id) {
    PlayerInfo* player = server.getPlayer(id);
    player->team = getAppropriateTeam();
    server.updatePlayerTable();
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

void GameServer::handlePlayerChangeTeam(int id) {
    PlayerInfo* player = server.getPlayer(id);
    tk_assert(player, "Invalid player ID received from client");
    player->team = player->team == Red ? Blue : Red;
    server.updatePlayerTable();
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

void GameServer::spawnShip(int player, Vec2f position) {
    PlayerInfo* info = server.getPlayer(player);
    tk_assert(info, "Invalid player ID for spawning a ship");
    info->ship = ships.spawn(player, position, -pi / 2, info->team);
    server.updatePlayerTable();

    tk_info(format("Spawned ship for %% at (%%, %%)", info->name, position.x, position.y));
}
