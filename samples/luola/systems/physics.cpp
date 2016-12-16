#include "physics.hpp"
#include "../components/position.hpp"
#include "../components/physics.hpp"
#include "../components/ship_control.hpp"

namespace {
    const Vec2f gravity = { 0, 200 };
    const float drag = 0.005f;
    const float mass = 1;
}

void PhysicsSystem::update(float dt, EntityCollection& entities) {
    updateShipInput(dt, entities);
    updatePhysics(dt, entities);
}

void PhysicsSystem::updateShipInput(float dt, EntityCollection& entities) {
    entities.map((std::function<void(ShipControl*, PhysicsComponent*, PositionComponent*)>)
                 [&](ShipControl* control, PhysicsComponent* physics, PositionComponent* position) {
        if (control->input.thrust) {
            physics->velocity += Vec2f{ std::cos(position->rotation), std::sin(position->rotation) } * 500.0f * dt;
        }
        if (control->input.left) {
            position->rotation -= 4 * dt;
        }
        if (control->input.right) {
            position->rotation += 4 * dt;
        }
    });
}

void PhysicsSystem::updatePhysics(float dt, EntityCollection& entities) {
    entities.map(std::function<void(PositionComponent*, PhysicsComponent*)>([&] (PositionComponent* pos, PhysicsComponent* phys) {
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
