#include "lobby.hpp"
#include "playground.hpp"
#include "../menu/cursor.hpp"

Lobby::Lobby(Global& global) :
    GameState(global),
    tweens(global) {

    Cursor::set(Cursor::Arrow);

    global.input.onMouseUp.attach(onRelease, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
        }
    });

    global.input.onMouseDown.attach(onClick, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
        }
    });

    global.input.onMouseMove.attach(onMove, [&] (Vec2i position) {
    });

    buildLobby();
}

GameState* Lobby::update(float dt) {
    tweens.update();

    return GameState::update(dt);
}

void Lobby::shutdown() { }

void Lobby::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    for (auto& ptr : elements) {
        ptr->draw(projection);
    }
}

void Lobby::buildLobby() {
    addText("Lobby", 40, { 50, 50 }, { 1, 1, 1, 1 });
}

void Lobby::addText(const std::string& text, int size, const Vec2f& position, const Vec4f& color) {
    Font* font = global.cache.get<Font>("font");
    Shader* shader = global.cache.get<Shader>("shader");
    Text* element = new Text(font, shader, position, text, size);
    element->setColor(color);
    elements.emplace_back(element);
}
