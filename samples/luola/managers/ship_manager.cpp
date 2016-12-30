#include "ship_manager.hpp"
#include "../menu/text.hpp"

ShipManager::ShipManager(Global& global) : global(global), id(0) {}

int ShipManager::spawn(int owner, const Vec2f& position, float rotation) {
    spawnWithID(id, owner, position, rotation);
    return id++;
}

Ship* ShipManager::spawnWithID(int id, int owner, const Vec2f& position, float rotation) {
    tk_assert(ships.count(id) == 0, "Ship with ID already exists!");
    int team = id % 2;
    Vec4f color = Vec4f{(float)team, 0, (float)!team, 1};
    ships.emplace(id, Ship(global, position, rotation, team, owner, color));
    return &ships.at(id);
}

Ship* ShipManager::get(int id) {
    return ships.count(id) ? &ships.at(id) : nullptr;
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

ShipManager::iterator ShipManager::begin() {
    return ships.begin();
}

ShipManager::iterator ShipManager::end() {
    return ships.end();
}
