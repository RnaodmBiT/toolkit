#pragma once

#include "global.hpp"

class Playground : public GameState {

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
