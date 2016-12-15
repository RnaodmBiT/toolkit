#include "playground.hpp"

#include "entity.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {
    addGameTypes();

    factory.build("thing", entities, Vec2f{ 200, 100 });
}

GameState* Playground::update(float dt) {

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
    factory.addType("thing", EntityFactory::Builder([&] (EntityCollection& collection, Blob::const_iterator& blob) {
        Vec2f position;
        deserialize(blob, position);

        Entity& e = collection.create();
        e.add<PositionComponent>(position);
        e.add<PhysicsComponent>();
        e.add<DrawableComponent>(Shape::rectangle({ 0, 0 }, { 100, 100 }),
                                 global.cache.get<Shader>("shader"),
                                 nullptr);
    }));
}
