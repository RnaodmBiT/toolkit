#pragma once

#include "../global.hpp"
#include "../menu/menu.hpp"
#include "../menu/panel.hpp"
#include "../menu/text.hpp"
#include "../entities/background.hpp"
#include "../managers/tween_manager.hpp"


class Title : public GameState {
    TweenManager tweens;
    Text title;
    Menu menu;

    Panel join, host, options;
    Panel* activePanel;

    Background background;
    Vec2f backgroundPosition;

    Delegate<int, Vec2i> onClick, onRelease;
    Delegate<Vec2i> onMove;

    void buildMenu();
    void buildJoinPanel();
    void buildHostPanel();
    void buildOptionsPanel();

    void showPanel(Panel& panel);

public:

    Title(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
