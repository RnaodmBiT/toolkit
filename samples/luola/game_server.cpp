#include "messages.hpp"
#include "game_server.hpp"

GameServer::GameServer() : networkTick(30) {
    onConnect.event = [&] (int id) {
        spawnShip(id, { 400, 100 }, { 0, 0, 1, 1 });
    };

    onDisconnect.event = [&] (int id) {
        deleteShip(id);
    };

    server.onPlayerConnected.attach(onConnect);
    server.onPlayerDisconnected.attach(onDisconnect);
}

void GameServer::startServer(int port) {
    server.start(port);
}

void GameServer::update(float dt) {
    server.pollEvents();

    for (auto& ship : ships) {
        ship.update(dt);
    }

    if (networkTick.update()) {
        Host::Packet update;
        serialize(update, (uint8_t)LuolaMessage::UpdateShips, (int)ships.size());
        for (auto& ship : ships) {
            serialize(update, ship.getID(), ship.getPosition(), ship.getAngle());
        }
        server.broadcast(false, update);
    }
}

void GameServer::spawnShip(int player, Vec2f position, Vec4f color) {
    ships.emplace_back(player, position, color, nullptr);
}

void GameServer::deleteShip(int player) {
    auto it = std::find_if(ships.begin(), ships.end(), [&] (const Ship& ship) {
        return ship.getID() == player;
    });
    ships.erase(it);
    server.broadcast(true, (uint8_t)LuolaMessage::DeleteShip, player);
}