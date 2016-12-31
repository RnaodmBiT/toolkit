#pragma once

#include "../global.hpp"
#include "../menu/menu.hpp"
#include "../menu/panel.hpp"
#include "../menu/text.hpp"
#include "../menu/button.hpp"
#include "../entities/background.hpp"
#include "../managers/tween_manager.hpp"


class Lobby : public GameState {
    TweenManager tweens;
    std::vector<std::unique_ptr<Element>> elements;
    std::vector<Text*> blueTeam;
    std::vector<Text*> redTeam;

    Delegate<int, Vec2i> onClick, onRelease;
    Delegate<Vec2i> onMove;
    Delegate<> onDisconnectedFromServer;

    Menu menu;

    Text* addText(const std::string& text, int size, const Vec2f& position, const Vec4f& color);
    Button* addButton(const std::string& text, int size, const Vec2f& position);

    void buildLobby();
    void buildPlayerList();

    void updateTeamLists();

public:

    Lobby(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
