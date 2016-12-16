#include "playground.hpp"

#include "entity.hpp"
#include "shapes.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"
#include "components/ship_control.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {
    addGameTypes();

    factory.build("ship", entities, Vec2f{ 200, 100 }, Vec4f{ 0, 0, 1, 1 });
}

GameState* Playground::update(float dt) {

    entities.map((std::function<void(ShipControl*)>)[&](ShipControl* control) {
        control->input.thrust = global.input.isKeyDown(SDLK_w);
        control->input.left = global.input.isKeyDown(SDLK_a);
        control->input.right = global.input.isKeyDown(SDLK_d);
    });

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
        e.add<DrawableComponent>(createShipShape(color),
                                 global.cache.get<Shader>("shader"),
                                 nullptr);
        e.add<ShipControl>();
    }));
}
