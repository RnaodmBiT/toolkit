#include "ship_manager.hpp"

ShipManager::ShipManager(Global& global) : global(global), id(0) { }

int ShipManager::spawn(const Vec2f& position, float rotation) {
    spawnWithID(id, position, rotation);
    return id++;
}

Ship* ShipManager::spawnWithID(int id, const Vec2f& position, float rotation) {
    tk_assert(ships.count(id) == 0, "Ship with ID already exists!");
    ships.insert({ id, Ship(global, position, rotation) });
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

void ShipManager::render(const Mat4f& projection) {
    for (auto& pair : ships) {
        pair.second.render(projection);
    }
}
