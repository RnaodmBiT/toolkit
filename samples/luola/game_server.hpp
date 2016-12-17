#pragma once
#include <core.hpp>
#include <net.hpp>
#include "player_info.hpp"
#include "managers/ship_manager.hpp"

using namespace tk::core;
using namespace tk::net;

struct Global;

class GameServer {
    Global& global;

    Server<PlayerInfo> server;
    UpdateTimer updateTimer;

    ShipManager ships;

    Delegate<int, const Host::Packet&> onMessageReceived;
    Delegate<int> onPlayerConnected, onPlayerDisconnected;

    void handleMessage(int id, const Host::Packet& data);
    void handlePlayerConnect(int id);
    void handlePlayerDisconnect(int id);

public:

    GameServer(Global& global);

    void update(float dt);

};