#include "ship_manager.hpp"
#include "../menu/text.hpp"

ShipManager::ShipManager(Global& global) : global(global), id(0) {}

int ShipManager::spawn(const Vec2f& position, float rotation) {
    spawnWithID(id, position, rotation);
    return id++;
}

Ship* ShipManager::spawnWithID(int id, const Vec2f& position, float rotation) {
    tk_assert(ships.count(id) == 0, "Ship with ID already exists!");
    int team = id % 2;
    Vec4f color = Vec4f{(float)team, 0, (float)!team, 1};
    ships.emplace(id, Ship(global, position, rotation, team, color));
    return &ships.at(id);
}

Ship* ShipManager::get(int id) {
    return ships.count(id) ? &ships.at(id) : nullptr;
}

void ShipManager::removeShip(int id) {
    ships.erase(id);
}

void ShipManager::update(float dt) {
    for (auto& pair : ships) {
        pair.second.update(dt);
    }
}

void ShipManager::draw(const Mat4f& projection, tk::net::PlayerTable<PlayerInfo> players) {
    for (auto& pair : ships) {
        pair.second.draw(projection);
    }
    Text ship_text = Text(global.cache.get<Font>("font"), global.cache.get<Shader>("shader"), Vec2f{ 0,0 }, "name", 15);
    for (int i = 0; i < players.playerList.size(); i++) {
        int current = players.playerList[i].info.ship;
        if (ships.count(current)) {
            std::string name = players.playerList[i].info.name;
            ship_text.setPosition(Vec2f{ -(float)(name.length() * 3.5), -35 } +ships.at(current).getPosition());
            ship_text.setText(name, 15);
            ship_text.draw(projection);
        }
    }
}

void ShipManager::checkHealth() {
    for (auto& ship : ships) {
        if (ship.second.getHealth() <= 0) {
            removeShip(ship.first);
        }
    }
}

ShipManager::iterator ShipManager::begin() {
    return ships.begin();
}

ShipManager::iterator ShipManager::end() {
    return ships.end();
}
