#include "game.hpp"
#include <SDL.h>

void Game::create(Global& g) {
    global = &g;

    Font* font = global->resources.get<Font>("font");
    Shader* shader = global->resources.get<Shader>("shader");

    scene.reset(new DrawableNode("scene"));
    scene->setShader(shader);
}

void Game::shutdown() {
}

LuolaState* Game::update() {
    return LuolaState::update();
}

void Game::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global->resolution.x, (float)global->resolution.y);
    scene->draw(projection);
}

