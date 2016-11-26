#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Title : public LuolaState {
    Global* global;

    std::unique_ptr<DrawableNode> scene;

    std::unique_ptr<TextNode> title;

public:
    void create(Global& global);
    LuolaState* update();
    void draw();
    void shutdown();
};
