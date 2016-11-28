#include "game.hpp"
#include <SDL.h>

void Game::createShip() {
    Vec2f points[] = {
        { 10, 0 },
        { -5, 7.5f },
        { -2.5f, 0 },

        { 10, 0 },
        { -2.5f, 0 },
        { -5, -7.5f }
    };

    Vec4f colors[] = {
        { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
        { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
    };

    Vec2f uvs[] = {
        { 0, 0 }, { 0, 0 }, { 0, 0 },
        { 0, 0 }, { 0, 0 }, { 0, 0 },
    };

    shapeShip = Shape::polygon(points, colors, uvs, sizeof_array(points));
}

Game::Game(Global& global) : LuolaState(global) {
    Font* font = global.resources.get<Font>("font");
    Shader* shader = global.resources.get<Shader>("shader");

    createShip();

    scene.reset(new DrawableNode("scene"));
    scene->setShader(shader);

    ShapeNode* playerNode = new ShapeNode("player", &shapeShip);
    scene->addChild(playerNode);

    player = Ship({ 400.0f, 100.0f }, playerNode, { 0.0f, 0.0f, 1.0f, 1.0f });
    playerController.reset(new PlayerController(global, player));
}

void Game::shutdown() {
}

LuolaState* Game::update(float dt) {
    playerController->update(global, dt);
    player.update(dt);

    return LuolaState::update(dt);
}

void Game::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, (float)global.resolution.x, (float)global.resolution.y);
    scene->draw(projection);
}

