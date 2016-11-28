#include "title.hpp"
#include "game.hpp"
#include <SDL.h>

Title::Title(Global& global) : LuolaState(global) {
    Font* font = global.resources.get<Font>("font");
    Shader* shader = global.resources.get<Shader>("shader");

    scene.reset(new DrawableNode("scene"));
    scene->setShader(shader);

    title.reset(new TextNode("title", font, "LUOLA", 60));
    title->setTransform(translate(50.0f, 50.0f, 0.0f));
    scene->addChild(title.get());

    keyPress.event = [this] (int key) {
        setNextState(new Game(this->global));
    };
    global.keyboard.keyPress.attach(keyPress);
}

void Title::shutdown() {
}

LuolaState* Title::update(float dt) {
    return LuolaState::update(dt);
}

void Title::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global.resolution.x, (float)global.resolution.y);
    scene->draw(projection);
}

