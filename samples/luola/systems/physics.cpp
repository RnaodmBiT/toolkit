#include "physics.hpp"
#include "../components/position.hpp"
#include "../components/physics.hpp"

namespace {
    const Vec2f gravity = { 0, 200 };
    const float drag = 0.005f;
    const float mass = 1;
}

void PhysicsSystem::update(float dt, EntityCollection& entities) {
    entities.map<PositionComponent, PhysicsComponent>(
        std::function<void(PositionComponent*, PhysicsComponent*)>([&] (PositionComponent* pos, PhysicsComponent* phys) {
        pos->position += phys->velocity * dt;
        phys->velocity += gravity * dt;

        float force = phys->velocity.lengthSquared() * drag;
        phys->velocity -= phys->velocity.normalized() * (force * dt / mass);

        if (pos->position.y > 500) {
            pos->position.y = 500;
            phys->velocity.y = 0;
        }
    }));
}
