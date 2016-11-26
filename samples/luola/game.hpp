#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Game : public LuolaState {
    Global* global;

    std::unique_ptr<DrawableNode> scene;

public:
    void create(Global& global);
    LuolaState* update();
    void draw();
    void shutdown();
};
