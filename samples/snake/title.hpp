#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <layout.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;
using namespace tk::layout;

class Title : public SnakeState {
    Global* global;

    std::unique_ptr<DrawableNode> scene;

    std::unique_ptr<TextNode> title, hello;

public:
    void create(Global& global);
    SnakeState* update();
    void draw();
    void shutdown();
};