#pragma once

#include "../global.hpp"
#include "../text.hpp"
#include "../menu/menu.hpp"

class Title : public GameState {
    Text title;
    Menu menu;

    Delegate<int, Vec2i> onClick, onRelease;
    Delegate<Vec2i> onMove;

public:

    Title(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
