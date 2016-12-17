#include "projectile_manager.hpp"

ProjectileManager::ProjectileManager(Global& global) : global(global), id(0) { }

int ProjectileManager::spawn(const Vec2f& position, const Vec2f& shipVelocity, float rotation) {
    spawnWithID(id, position, shipVelocity, rotation);
    return id++;
}

Projectile* ProjectileManager::spawnWithID(int id, const Vec2f& position, const Vec2f& shipVelocity, float rotation) {
    tk_assert(projectiles.count(id) == 0, "Projectile with ID already exists!");
    projectiles.insert({ id, Projectile(global, position, shipVelocity, rotation) });
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

void ProjectileManager::render(const Mat4f& projection) {
    for (auto& pair : projectiles) {
        pair.second.render(projection);
    }
}
