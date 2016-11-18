#include "game.hpp"
#include <SDL.h>

void Game::create(Global& g) {
    global = &g;

    Font* font = global->resources.get<Font>("font");
    Shader* shader = global->resources.get<Shader>("shader");

    Vec2f size{ 20, 100 };
    paddle = Shape::rectangle(-size / 2.0f, size);

    leftPosition = { 50.0f, 288.0f, 0.0f };
    rightPosition = { 1024.0f - 50.0f, 288.0f, 0.0f };

    leftPaddle.reset(new ShapeNode("left", paddle, translate(leftPosition), shader));
    leftPaddle->setTint({ 1.0f, 0.0f, 0.0f, 1.0f });
    rightPaddle.reset(new ShapeNode("right", paddle, translate(rightPosition), shader));
    rightPaddle->setTint({ 0.0f, 0.0f, 1.0f, 1.0f });

    title.reset(new TextNode("title", font, "PONG", 50, translate(10.0f, 10.0f, 0.0f), shader));

    scene.reset(new DrawableNode("scene"));
    scene->addChild(leftPaddle.get());
    scene->addChild(rightPaddle.get());
    scene->addChild(title.get());
}


void Game::shutdown() {
}


PongState* Game::update() {
    if (global->keyboard.isKeyDown(SDLK_w)) {
        leftPosition.y -= 1.0f;
    }
    if (global->keyboard.isKeyDown(SDLK_s)) {
        leftPosition.y += 1.0f;
    }

    return PongState::update();
}


void Game::draw() {
    leftPaddle->setTransform(translate(leftPosition));
    rightPaddle->setTransform(translate(rightPosition));

    Mat4f projection = orthographic(0.0f, 0.0f, 1024.0f, 576.0f);
    scene->draw(projection);
}