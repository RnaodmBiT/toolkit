#pragma once

#include "global.hpp"
#include "managers/ship_manager.hpp"

class Playground : public GameState {
    Client<PlayerInfo> client;

    ShipManager ships;
    int player;

    Delegate<const Host::Packet&> onMessageReceived;

    void handleMessage(const Host::Packet& data);
    void handleShipUpdate(Host::Packet::const_iterator& data);

    void handlePlayerInput();

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
