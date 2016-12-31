#include "projectile_manager.hpp"
#include "../physics.hpp"

ProjectileManager::ProjectileManager(Global& global) : global(global), id(0) { }

int ProjectileManager::spawn(const Vec2f& position, const Vec2f& shipVelocity, float rotation) {
    spawnWithID(id, position, shipVelocity, rotation);
    return id++;
}

Projectile* ProjectileManager::spawnWithID(int id, const Vec2f& position, const Vec2f& shipVelocity, float rotation) {
    tk_assert(projectiles.count(id) == 0, "Projectile with ID already exists!");
    projectiles.emplace(id, Projectile(global, position, shipVelocity, rotation));
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

void ProjectileManager::checkCollisions(ShipManager* ship_man, float dt) {
    for (auto& ship_pair : *ship_man) {
        for (auto& proj_pair : projectiles) {
            if (bullet_collision(&ship_pair.second, &proj_pair.second, dt)) {
                removeProjectile(proj_pair.first);
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