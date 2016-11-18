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

    std::unique_ptr<TextNode> title;

    tk::graphics::Shape paddle;
    std::unique_ptr<ShapeNode> leftPaddle;
    std::unique_ptr<ShapeNode> rightPaddle;

    Vec3f leftPosition, rightPosition;

public:
    void create(Global& global);
    PongState* update();
    void draw();
    void shutdown();
};