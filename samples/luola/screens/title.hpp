#pragma once

#include "../global.hpp"
#include "../menu/menu.hpp"
#include "../menu/panel.hpp"
#include "../menu/text.hpp"

class Title : public GameState {
    Text title;
    Menu menu;

    Panel join, host, options;
    Panel* activePanel;

    Delegate<int, Vec2i> onClick, onRelease;
    Delegate<Vec2i> onMove;

    void buildMenu();
    void buildJoinPanel();
    void buildHostPanel();
    void buildOptionsPanel();

public:

    Title(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
