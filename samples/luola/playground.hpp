#pragma once

#include "global.hpp"
#include "entity.hpp"
#include "systems/physics.hpp"
#include "systems/rendering.hpp"

class Playground : public GameState {
    EntityCollection entities;
    EntityFactory factory;

    PhysicsSystem physics;
    RenderingSystem rendering;


    void addGameTypes();

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
