#pragma once

#include "../global.hpp"
#include "../menu/menu.hpp"
#include "../menu/panel.hpp"
#include "../menu/text.hpp"
#include "../entities/background.hpp"
#include "../managers/tween_manager.hpp"


class Lobby : public GameState {
    TweenManager tweens;
    std::vector<std::unique_ptr<Element>> elements;

    Delegate<int, Vec2i> onClick, onRelease;
    Delegate<Vec2i> onMove;

    void addText(const std::string& text, int size, const Vec2f& position, const Vec4f& color);

    void buildLobby();

public:

    Lobby(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
