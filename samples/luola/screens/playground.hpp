#pragma once


#include "../global.hpp"
#include "../managers/ship_manager.hpp"
#include "../managers/projectile_manager.hpp"
#include "../camera.hpp"
#include "../entities/background.hpp"

class Playground : public GameState {
    Client<PlayerInfo> client;

    Camera camera;
    ShipManager ships;
    ProjectileManager projectiles;
    Background background;

    ShipInput playerInput;
    UpdateTimer playerInputTimer;

    Delegate<int> onKeyDown;
    Delegate<const Host::Packet&> onMessageReceived;

    void handleMessage(const Host::Packet& data);
    void handleShipUpdate(Host::Packet::const_iterator& data);
    void handleProjectileUpdate(Host::Packet::const_iterator& data);

    void handlePlayerInput();

    void updateCamera(float dt);

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
