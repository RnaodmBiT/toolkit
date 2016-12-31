#include "ship_manager.hpp"
#include "../menu/text.hpp"

ShipManager::ShipManager(Global& global) : global(global), id(0) { }

int ShipManager::spawn(int owner, const Vec2f& position, float rotation, Team team) {
    spawnWithID(id, owner, position, rotation, team);
    return id++;
}

Ship* ShipManager::spawnWithID(int id, int owner, const Vec2f& position, float rotation, Team team) {
    tk_assert(ships.count(id) == 0, "Ship with ID already exists!");

    Vec4f color{ 1, 1, 1, 1 };
    if (team == Team::Red) {
        color = { 1, 0, 0, 1 };
    } else if (team == Team::Blue) {
        color = { 0, 0, 1, 1 };
    }

    ships.emplace(id, Ship(global, position, rotation, team, owner, color));
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

void ShipManager::draw(const Mat4f& projection) {
    for (auto& pair : ships) {
        pair.second.draw(projection);
    }
}

void ShipManager::checkHealth() {
    for (auto it = ships.begin(); it != ships.end(); ) {
        if (it->second.getHealth() <= 0) {
            it = ships.erase(it);
        } else {
            it++;
        }
    }
}

ShipManager::iterator ShipManager::begin() {
    return ships.begin();
}

ShipManager::iterator ShipManager::end() {
    return ships.end();
}
