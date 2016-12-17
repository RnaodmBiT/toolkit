#pragma once
#include <core.hpp>
#include <net.hpp>
#include "player_info.hpp"
#include "managers/ship_manager.hpp"
#include "managers/projectile_manager.hpp"

using namespace tk::core;
using namespace tk::net;

struct Global;

class GameServer {
    Global& global;

    Server<PlayerInfo> server;
    UpdateTimer updateTimer;

    ShipManager ships;
    ProjectileManager projectiles;

    Delegate<int, const Host::Packet&> onMessageReceived;
    Delegate<int> onPlayerConnected, onPlayerDisconnected;

    void handleMessage(int id, const Host::Packet& data);
    void handlePlayerConnect(int id);
    void handlePlayerDisconnect(int id);

    void handlePlayerInput(int id, Host::Packet::const_iterator& it);

    void shootBullets();

public:

    GameServer(Global& global);

    void update(float dt);

};