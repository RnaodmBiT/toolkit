#pragma once

#include "global.hpp"
#include "entity.hpp"

class Playground : public GameState {
    EntityCollection entities;
public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
