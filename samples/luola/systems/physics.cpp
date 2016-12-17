#include "physics.hpp"
#include "../components/position.hpp"
#include "../components/physics.hpp"
#include "../components/projectile.hpp"

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

	entities.map<PositionComponent, ProjectileComponent>(
		std::function<void(PositionComponent*, ProjectileComponent*)>([&](PositionComponent* pos, ProjectileComponent* proj) {
		pos->position += proj->velocity * dt;
		proj->velocity += gravity * dt;

		float force = proj->velocity.lengthSquared() * drag;
		proj->velocity -= proj->velocity.normalized() * (force * dt / mass);
		pos->rotation = atan2f(proj->velocity.y,proj->velocity.x);

		if (pos->position.y > 500) {
			pos->position.y = 500;
			proj->velocity.y = 0;
		}
	}));
}
