#pragma once

#include "../includes.hpp"
#include "../global.hpp"
#include "../managers/ship_manager.hpp"
#include "../managers/projectile_manager.hpp"
#include "../camera.hpp"
#include "../entities/background.hpp"

struct ShipState {
    int tick;
    Vec2f position;
    float rotation;
};

struct ClientShip {
    std::vector<ShipState> history;
    ShipState render;
};

class Playground : public GameState {
    Camera camera;
    Background background;

    Shape shipShape;
    Shader* shader;

    std::unordered_map<int, ClientShip> ships;

    int latestServerTick, previousTick, clientTick;
    UpdateTimer gameUpdateTimer;

    ShipInput playerInput;
    UpdateTimer playerInputTimer;

    Delegate<int> onKeyDown;
    Delegate<const Host::Packet&> onMessageReceived;
    Delegate<> onDisconnectedFromServer;

    void handleMessage(const Host::Packet& data);
    void handleGameUpdate(Host::Packet::const_iterator& data);

    void handlePlayerInput();

    void updateCamera(float dt);

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
