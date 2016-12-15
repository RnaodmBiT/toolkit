#include "physics.hpp"
#include "../components/position.hpp"
#include "../components/physics.hpp"

void PhysicsSystem::update(float dt, EntityCollection& entities) {
    entities.map<PositionComponent, PhysicsComponent>(
        std::function<void(PositionComponent*, PhysicsComponent*)>([&] (PositionComponent* pos, PhysicsComponent* phys) {
        pos->position += phys->velocity * dt;
        phys->velocity.y += 100 * dt;

        if (pos->position.y > 500) {
            pos->position.y = 500;
            phys->velocity.y = 0;
        }
    }));
}
