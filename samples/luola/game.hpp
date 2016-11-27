#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"
#include "ship.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Game : public LuolaState {
    Global* global;

    std::unique_ptr<DrawableNode> scene;

    Shape shapeShip;

    Ship player;

    void createShip();

public:
    void create(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
