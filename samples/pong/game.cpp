#include "game.hpp"
#include <SDL.h>

void Game::create(Global& g) {
    global = &g;

    Font* font = global->resources.get<Font>("font");
    Shader* shader = global->resources.get<Shader>("shader");

    Vec2f size{ 20, 100 };
    paddle = Shape::rectangle(-size / 2.0f, size);
    circle = Shape::circle({ 0, 0 }, 10);

    leftPosition = { 50.0f, 288.0f, 0.0f };
    rightPosition = { 1024.0f - 50.0f, 288.0f, 0.0f };
    ballPosition = { 512.0f, 288.0f, 0.0f };
    ballSpeed = { -300.0f, -100.0f, 0.0f };

    leftPaddle.reset(new ShapeNode("left", paddle, translate(leftPosition), shader));
    leftPaddle->setTint({ 1.0f, 0.0f, 0.0f, 1.0f });

    rightPaddle.reset(new ShapeNode("right", paddle, translate(rightPosition), shader));
    rightPaddle->setTint({ 0.0f, 0.0f, 1.0f, 1.0f });

    ball.reset(new ShapeNode("ball", circle, translate(ballPosition), shader));
    ball->setTint({ 0.0f, 1.0f, 0.0f, 1.0f });

    title.reset(new TextNode("title", font, "PONG", 50, translate(10.0f, 10.0f, 0.0f), shader));
    score.reset(new TextNode("score", font, "0 | 0", 40, translate(500.0f, 20.0f, 0.0f), shader));

    scene.reset(new DrawableNode("scene"));
    scene->addChild(leftPaddle.get());
    scene->addChild(rightPaddle.get());
    scene->addChild(ball.get());
    scene->addChild(title.get());
    scene->addChild(score.get());
}


void Game::shutdown() {
}


PongState* Game::update() {
    if (global->keyboard.isKeyDown(SDLK_w)) {
        leftPosition.y -= 5.0f;
    }
    if (global->keyboard.isKeyDown(SDLK_s)) {
        leftPosition.y += 5.0f;
    }
    if (global->keyboard.isKeyDown(SDLK_UP)) {
        rightPosition.y -= 5.0f;
    }
    if (global->keyboard.isKeyDown(SDLK_DOWN)) {
        rightPosition.y += 5.0f;
    }

    ballPosition += ballSpeed * 1.0f / 60.0f;

    if (ballPosition.y < 10) {
        ballPosition.y = 10;
        ballSpeed.y *= -1;
    }

    if (ballPosition.y > 566) {
        ballPosition.y = 566;
        ballSpeed.y *= -1;
    }

    if (ballPosition.x < 10) {
        rightScore++;
        ballPosition = { 512.0f, 288.0f, 0.0f };
        ballSpeed.x *= -1;
    }

    if (ballPosition.x > 1014.0f) {
        leftScore++;
        ballPosition = { 512.0f, 288.0f, 0.0f };
        ballSpeed.x *= -1;
    }

    if (isBallTouchingPaddle(leftPosition) && ballSpeed.x < 0) {
        ballSpeed.x *= -1;
    }

    if (isBallTouchingPaddle(rightPosition) && ballSpeed.x > 0) {
        ballSpeed.x *= -1;
    }


    return PongState::update();
}


void Game::draw() {
    score->setText(format("%% | %%", leftScore, rightScore), 40);
    const Vec2i& size = score->getSize();
    score->setTransform(translate(512.0f - float(size.x) / 2, 20.0f, 0.0f));

    leftPaddle->setTransform(translate(leftPosition));
    rightPaddle->setTransform(translate(rightPosition));
    ball->setTransform(translate(ballPosition));

    Mat4f projection = orthographic(0.0f, 0.0f, 1024.0f, 576.0f);
    scene->draw(projection);
}


bool Game::isBallTouchingPaddle(const Vec3f& position) {
    Vec3f size{ 20 / 2 + 10, 100 / 2 + 10, 0 };

    Vec3f delta = ballPosition - position;
    return std::abs(delta.x) < size.x && std::abs(delta.y) < size.y;
}