#include "projectile_manager.hpp"
#include "../physics.hpp"

ProjectileManager::ProjectileManager(Global& global) : global(global), id(0) { }

int ProjectileManager::spawn(const Vec2f& position, const Vec2f& shipVelocity, float rotation, int type) {
    spawnWithID(id, position, shipVelocity, rotation, type);
    return id++;
}

Projectile* ProjectileManager::spawnWithID(int id, const Vec2f& position, const Vec2f& shipVelocity, float rotation, int type) {
    tk_assert(projectiles.count(id) == 0, "Projectile with ID already exists!");
    projectiles.emplace(id, Projectile(global, position, shipVelocity, rotation, type));
    return &projectiles.at(id);
}

Projectile* ProjectileManager::get(int id) {
    return projectiles.count(id) ? &projectiles.at(id) : nullptr;
}

void ProjectileManager::update(float dt) {
    for (auto& pair : projectiles) {
        pair.second.update(dt);
    }
}

void ProjectileManager::removeProjectile(int id) {
    projectiles.erase(id);
}

void ProjectileManager::checkCollisions(ShipManager& ships) {
    for (auto& ship : ships) {
        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            if (bulletCollision(ship.second, it->second)) {
                it = projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void ProjectileManager::draw(const Mat4f& projection) {
    for (auto& pair : projectiles) {
        pair.second.draw(projection);
    }
}

ProjectileManager::iterator ProjectileManager::begin() {
    return projectiles.begin();
}

ProjectileManager::iterator ProjectileManager::end() {
    return projectiles.end();
}