#pragma once

#include "../global.hpp"
#include "../text.hpp"

class Title : public GameState {
    Text title;

public:

    Title(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
