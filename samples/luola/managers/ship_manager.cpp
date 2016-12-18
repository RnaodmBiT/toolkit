#include "ship_manager.hpp"

ShipManager::ShipManager(Global& global) : global(global), id(0) {
	colors.push_back(Vec4f{ 1,0,0,1 });
	colors.push_back(Vec4f{ 0,1,0,1 });
	colors.push_back(Vec4f{ 0,0,1,1 });
	colors.push_back(Vec4f{ 1,1,0,1 });
}

int ShipManager::spawn(const Vec2f& position, float rotation) {
    spawnWithID(id, position, rotation);
    return id++;
}

Ship* ShipManager::spawnWithID(int id, const Vec2f& position, float rotation) {
    tk_assert(ships.count(id) == 0, "Ship with ID already exists!");
    ships.emplace(id, Ship(global, position, rotation, colors[id]));
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

ShipManager::iterator ShipManager::begin() {
    return ships.begin();
}

ShipManager::iterator ShipManager::end() {
    return ships.end();
}
