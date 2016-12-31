#include "lobby.hpp"
#include "playground.hpp"
#include "../menu/cursor.hpp"
#include "../messages.hpp"
#include "title.hpp"

Lobby::Lobby(Global& global) :
    GameState(global),
    tweens(global),
    menu(global) {

    Cursor::set(Cursor::Arrow);

    global.input.onMouseUp.attach(onRelease, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseUp();
            for (auto& ptr : elements) {
                ptr->mouseUp();
            }
        }
    });

    global.input.onMouseDown.attach(onClick, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseDown();
            for (auto& ptr : elements) {
                ptr->mouseDown();
            }
        }
    });

    global.input.onMouseMove.attach(onMove, [&] (Vec2i position) {
        Vec2f pos{ (float)position.x, (float)position.y };
        menu.mouseMove(pos);
        for (auto& ptr : elements) {
            ptr->mouseMove(pos);
        }
    });

    global.client->onServerDisconnected.attach(onDisconnectedFromServer, [&] () {
        setNextState(new Title(global));
    });

    buildLobby();
}

GameState* Lobby::update(float dt) {
    global.updateNetwork(dt);
    tweens.update();

    updateTeamLists();

    return GameState::update(dt);
}

void Lobby::shutdown() {
    global.client->disconnect();
    if (global.server) {
        global.server.reset();
    }
}

void Lobby::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    menu.draw(projection);
    for (auto& ptr : elements) {
        ptr->draw(projection);
    }
}

void Lobby::buildLobby() {
    addText("Lobby", 40, { 50, 50 }, { 1, 1, 1, 1 });

    buildPlayerList();

    menu.addButton("Change Team", 20)->onClick = [&] () {
        global.client->send(true, (uint8_t)PlayerChangeTeam);
    };

    menu.addSpace(20);

    if (global.server) {
        menu.addButton("Start", 20)->onClick = [&] () {
            // global.server->startGame();
        };
    }

    menu.addButton("Disconnect", 20)->onClick = [&] () {
        setNextState(new Title(global));
    };

    menu.setPosition({ 50, (float)global.height - 50 - menu.getSize().y });
}

void Lobby::buildPlayerList() {
    Vec2f position{ (float)global.width - 600, 100 };

    addText("Blue", 24, position + Vec2f{ 0, 0 }, { 0, 0, 1, 1 });
    addText("Red", 24, position + Vec2f{ 200, 0 }, { 1, 0, 0, 1 });

    for (int i = 0; i < 8; ++i) {
        Text* blue = addText("  -", 16, position + Vec2f{ 0, 40 + 20 * (float)i }, { 0.3f, 0.3f, 1, 1 });
        Text* red = addText("  -", 16, position + Vec2f{ 200, 40 + 20 * (float)i }, { 1, 0.3f, 0.3f, 1 });

        blueTeam.push_back(blue);
        redTeam.push_back(red);
    }
}

Text* Lobby::addText(const std::string& text, int size, const Vec2f& position, const Vec4f& color) {
    Font* font = global.cache.get<Font>("font");
    Shader* shader = global.cache.get<Shader>("shader");
    Text* element = new Text(font, shader, position, text, size);
    element->setColor(color);
    elements.emplace_back(element);
    return element;
}

Button* Lobby::addButton(const std::string& text, int size, const Vec2f& position) {
    Button* element = new Button(global, position, text, size);
    elements.emplace_back(element);
    return element;
}

void Lobby::updateTeamLists() {
    int red = 0, blue = 0;
    for (int player : global.client->getPlayerIDs()) {
        PlayerInfo* info = global.client->getPlayer(player);
        if (info->team == Red) {
            redTeam[red]->setText(info->name, 16);
            if (player == global.client->id) {
                redTeam[red]->setColor({ 1, 0.8f, 0.8f, 1 });
            } else {
                redTeam[red]->setColor({ 1, 0.3f, 0.3f, 1 });
            }
            red++;
        } else {
            blueTeam[blue]->setText(info->name, 16);
            if (player == global.client->id) {
                blueTeam[blue]->setColor({ 0.8f, 0.8f, 1, 1 });
            } else {
                blueTeam[blue]->setColor({ 0.3f, 0.3f, 1, 1 });
            }
            blue++;
        }
    }

    for (int i = red; i < redTeam.size(); ++i) {
        redTeam[i]->setText("  -", 16);
        redTeam[i]->setColor({ 1, 0.3f, 0.3f, 1 });
    }

    for (int i = blue; i < blueTeam.size(); ++i) {
        blueTeam[i]->setText("  -", 16);
        blueTeam[i]->setColor({ 0.3f, 0.3f, 1, 1 });
    }
}
