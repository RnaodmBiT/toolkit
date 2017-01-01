#include "physics.hpp"

bool bulletCollision(Ship& ship, Projectile& bullet) {
    float size = 9;
    Vec2f delta = bullet.getPosition() - ship.getPosition();
    if (delta.lengthSquared() < size * size) {
        ship.takeDamage(10);
        ship.force(bullet.getVelocity() * projectileTypes[bullet.getType()].mass);
        return true;
    }
    return false;
}
