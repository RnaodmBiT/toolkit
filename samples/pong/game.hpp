#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Game : public PongState {
    Global* global;

    std::unique_ptr<DrawableNode> scene;

    std::unique_ptr<TextNode> title, score;

    tk::graphics::Shape paddle, circle;
    std::unique_ptr<ShapeNode> leftPaddle;
    std::unique_ptr<ShapeNode> rightPaddle;
    std::unique_ptr<ShapeNode> ball;

    Vec3f leftPosition, rightPosition, ballPosition, ballSpeed;

    int leftScore, rightScore;

    bool isBallTouchingPaddle(const Vec3f& paddle);

public:
    void create(Global& global);
    PongState* update();
    void draw();
    void shutdown();
};