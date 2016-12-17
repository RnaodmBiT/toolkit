#include "playground.hpp"

#include "entity.hpp"
#include "shapes.hpp"
#include "prv.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"
#include "components/ship_control.hpp"
#include "components/weaponary.hpp"
#include "components/projectile.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {
    addGameTypes();

    factory.build("ship", entities, Vec2f{ 200, 100 }, Vec4f{ 0, 0, 1, 1 });
}

GameState* Playground::update(float dt) {
	std::vector<PRV> bullets;

    entities.map<ShipControl>((std::function<void(ShipControl*)>)[&](ShipControl* control) {
        control->input.thrust = global.input.isKeyDown(SDLK_w);
        control->input.left = global.input.isKeyDown(SDLK_a);
        control->input.right = global.input.isKeyDown(SDLK_d);
		control->input.firing = global.input.isButtonDown(SDL_BUTTON_LEFT);
    });

    entities.map<ShipControl, PhysicsComponent, PositionComponent, WeponaryComponent>((std::function<void(ShipControl*, PhysicsComponent*, PositionComponent*, WeponaryComponent*)>)
        [&](ShipControl* control, PhysicsComponent* physics, PositionComponent* position, WeponaryComponent* weapon) {
        if (control->input.thrust) {
            physics->velocity += Vec2f{ std::cos(position->rotation), std::sin(position->rotation) } * 500.0f * dt;
        }
        if (control->input.left) {
            position->rotation -= 4 * dt;
        }
        if (control->input.right) {
            position->rotation += 4 * dt;
        }
		if (control->input.firing && weapon->reloadtime == 0) {
			bullets.push_back(PRV{position->position, position->rotation, physics->velocity});
			weapon->reloadtime = 1.0f;
		}
    });

	if (bullets.size() > 0) {
		for (int i = 0; i < bullets.size(); i++) {
			factory.build("bullet", entities, bullets[i].Position, bullets[i].Rotation, bullets[i].Velocity, Vec4f{ 1,1,1,1 });
		}
		bullets.clear();
	}

	entities.map<WeponaryComponent>((std::function<void(WeponaryComponent*)>)[&](WeponaryComponent* weapon) {
		weapon->reloadtime -= dt;
		if (weapon->reloadtime < 0) {
			weapon->reloadtime = 0;
		}
	});



    physics.update(dt, entities);

    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);
    rendering.render(entities, projection);
}

void Playground::shutdown() {

}

void Playground::addGameTypes() {
    factory.addType("ship", EntityFactory::Builder([&] (EntityCollection& collection, Blob::const_iterator& blob) {
        Vec2f position;
        Vec4f color;
        deserialize(blob, position, color);

        Entity& e = collection.create();
        e.add<PositionComponent>(position, -pi / 2);
        e.add<PhysicsComponent>();
		e.add<WeponaryComponent>();
        e.add<DrawableComponent>(createShipShape(color),
                                 global.cache.get<Shader>("shader"),
                                 nullptr);
        e.add<ShipControl>();
    }));

	factory.addType("bullet", EntityFactory::Builder([&](EntityCollection& collection, Blob::const_iterator& blob) {
		Vec2f position;
		float rotation;
		Vec2f velocity;
		Vec4f color;
		deserialize(blob, position, rotation, velocity, color);

		Entity& e = collection.create();
		e.add<PositionComponent>(position, rotation);
		velocity.x += 300 * cos(rotation);
		velocity.y += 300 * sin(rotation);
		e.add<ProjectileComponent>(velocity);
		e.add<DrawableComponent>(createBulletShape(color),
			global.cache.get<Shader>("shader"),
			nullptr);
	}));
}
