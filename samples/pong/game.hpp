#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

using namespace tk::core;
using namespace tk::graphics;

class Game : public State {
    std::unique_ptr<DrawableNode> scene;

    std::unique_ptr<TextNode> title;

    tk::graphics::Shape paddle;
    std::unique_ptr<ShapeNode> leftPaddle;
    std::unique_ptr<ShapeNode> rightPaddle;

public:
    void create(ResourceCollection& resources);
    State* update();
    void draw();
    void shutdown();
};