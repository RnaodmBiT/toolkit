#include "game.hpp"


void Game::create(ResourceCollection& resources) {
    Font* font = resources.get<Font>("font");
    Shader* shader = resources.get<Shader>("shader");

    Vec2f size{ 20, 100 };
    paddle = Shape::rectangle(-size / 2.0f, size);

    leftPaddle.reset(new ShapeNode("left", paddle, translate(50.0f, 288.0f, 0.0f), shader));
    leftPaddle->setTint({ 1.0f, 0.0f, 0.0f, 1.0f });
    rightPaddle.reset(new ShapeNode("right", paddle, translate(1024.0f - 50.0f, 288.0f, 0.0f), shader));
    rightPaddle->setTint({ 0.0f, 0.0f, 1.0f, 1.0f });

    title.reset(new TextNode("title", font, "PONG", 50, translate(10.0f, 10.0f, 0.0f), shader));

    scene.reset(new DrawableNode("scene"));
    scene->addChild(leftPaddle.get());
    scene->addChild(rightPaddle.get());
    scene->addChild(title.get());
}


void Game::shutdown() {
}


State* Game::update() {
    return State::update();
}


void Game::draw() {
    Mat4f projection = orthographic(0.0f, 0.0f, 1024.0f, 576.0f);
    scene->draw(projection);
}