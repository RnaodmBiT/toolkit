#include "playground.hpp"

#include "entity.hpp"
#include "components/position.hpp"

using namespace std::placeholders;

Playground::Playground(Global& global) : GameState(global) {

    Entity a, b, c;
    a.add<PositionComponent>(Vec2f{ 100, 100 });

    b.add<PositionComponent>(Vec2f{ 200, 200 });

    EntityCollection collection;
    collection.add(a);
    collection.add(b);
    collection.add(c);

    std::vector<Entity*> list = collection.filter<PositionComponent>();

    collection.map<PositionComponent>([] (PositionComponent* p) {
        printf("(%f, %f)\n", p->position.x, p->position.y);
    });

}

GameState* Playground::update(float dt) {

    return GameState::update(dt);
}

void Playground::draw() {

}

void Playground::shutdown() {

}

void Playground::printPosition(PositionComponent* p) {
    printf("(%f, %f)\n", p->position.x, p->position.y);
}
