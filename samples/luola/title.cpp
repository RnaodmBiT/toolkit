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

    instructions.reset(new TextNode("instructions", font, "[J] Join   [H] Host", 40));
    instructions->setTransform(translate(50.0f, 150.0f, 0.0f));
    scene->addChild(instructions.get());

    connectedToServer.event = [&] () {
        setNextState(new Game(global));
    };
    global.client.onConnectedToServer.attach(connectedToServer);

    keyPress.event = [&] (int key) {
        if (key == SDLK_j) {
            global.client.connect("localhost", 25140, { "Client" });
        }
        if (key == SDLK_h) {
            global.server.startServer(25140);
            global.client.connect("localhost", 25140, { "Server" });
            setNextState(new Game(global));
        }
    };
    global.keyboard.keyPress.attach(keyPress);
}

void Title::shutdown() {
}

LuolaState* Title::update(float dt) {
    global.client.pollEvents();
    return LuolaState::update(dt);
}

void Title::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global.resolution.x, (float)global.resolution.y);
    scene->draw(projection);
}

