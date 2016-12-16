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

    int id = factory.build("ship", entities, entities.getFreeID(), Vec2f{ 200, 100 }, Vec4f{ 0, 0, 1, 1 });
    entities.get(id).addTag("player");
}

GameState* Playground::update(float dt) {
    updatePlayerInput();
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
        int id;
        Vec2f position;
        Vec4f color;
        deserialize(blob, id, position, color);

        Entity& e = collection.create(id);
        e.add<PositionComponent>(position, -pi / 2);
        e.add<PhysicsComponent>();
        e.add<DrawableComponent>(createShipShape(color),
                                 global.cache.get<Shader>("shader"),
                                 nullptr);
        e.add<ShipControl>();
        return id;
    }));
}

void Playground::updatePlayerInput() {
    std::vector<Entity*> players = entities.filter<ShipControl>("player");
    for (auto player : players) {
        ShipInput& input = player->get<ShipControl>()->input;
        input.thrust = global.input.isKeyDown(SDLK_w);
        input.left = global.input.isKeyDown(SDLK_a);
        input.right = global.input.isKeyDown(SDLK_d);
    }
}
