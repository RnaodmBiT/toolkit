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
    PlayerInput input;

    Delegate<int> onKeyPress;
    Delegate<const Host::Packet&> clientOnMessageReceived;

    void createShipShape();

    void updateShips(Host::Packet::const_iterator msg);
    void handleDeleteShip(Host::Packet::const_iterator msg);

    void updatePlayerInput();
    Ship* getShip(int id);

public:
    Game(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
