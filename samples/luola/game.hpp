#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"
#include "ship.hpp"
#include "controller.hpp"

class Game : public LuolaState {
    std::unique_ptr<DrawableNode> scene;

    Shape shapeShip;

    std::vector<Ship> ships;

    Delegate<const Host::Packet&> clientOnMessageReceived;

    void createShipShape();

    void updateShips(Host::Packet::const_iterator msg);

public:
    Game(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
