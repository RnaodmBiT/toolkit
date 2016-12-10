#include "playground.hpp"

#include "entity.hpp"
#include "components/position.hpp"
#include "components/drawable.hpp"
#include "components/physics.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {

    Entity& a = entities.create();
    a.add<PositionComponent>(Vec2f{ 100, 100 });
    a.add<DrawableComponent>(Shape::rectangle({ 0, 0 }, { 100, 100 }),
                             global.cache.get<Shader>("shader"),
                             nullptr);
    a.add<PhysicsComponent>();
}

GameState* Playground::update(float dt) {

    entities.map<PositionComponent, PhysicsComponent>(
        std::function<void(PositionComponent*, PhysicsComponent*)>([&] (PositionComponent* pos, PhysicsComponent* phys) {
        pos->position += phys->velocity * dt;
        phys->velocity.y += 100 * dt;
    }));

    return GameState::update(dt);
}

void Playground::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    entities.map<PositionComponent, DrawableComponent>(
        std::function<void(PositionComponent*, DrawableComponent*)>([&](PositionComponent* p, DrawableComponent* d) {
        d->shader->apply();
        d->shader->setUniform("transform", projection * translate(p->position.x, p->position.y, 0.0f));
        d->shape.draw();
    }));
}

void Playground::shutdown() {

}