#include "title.hpp"
#include "game.hpp"
#include <SDL.h>

void Title::create(Global& g) {
    global = &g;

    Font* font = global->resources.get<Font>("font");
    Shader* shader = global->resources.get<Shader>("shader");

    scene.reset(new DrawableNode("scene"));
    scene->setShader(shader);

    title.reset(new TextNode("title", font, "LUOLA", 60));
    title->setTransform(translate(50.0f, 50.0f, 0.0f));
    scene->addChild(title.get());

    keyPress.event = [this] (int key) {
        tk_info("Moving to Game");
        setNextState(new Game);
    };
    global->keyboard.keyPress.attach(keyPress);
}

void Title::shutdown() {
}

LuolaState* Title::update(float dt) {
    return LuolaState::update(dt);
}

void Title::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global->resolution.x, (float)global->resolution.y);
    scene->draw(projection);
}

