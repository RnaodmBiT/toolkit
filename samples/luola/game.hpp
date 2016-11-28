#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"
#include "ship.hpp"
#include "controller.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Game : public LuolaState {
    std::unique_ptr<DrawableNode> scene;

    Shape shapeShip;

    Ship player;
    std::unique_ptr<Controller> playerController;

    void createShip();

public:
    Game(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
