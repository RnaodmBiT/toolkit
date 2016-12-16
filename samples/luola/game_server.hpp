#pragma once
#include <net.hpp>
#include "player_info.hpp"
#include "entity.hpp"
#include "systems/physics.hpp"

using namespace tk::core;
using namespace tk::net;

struct Global;

class GameServer {
    Global& global;

    Server<PlayerInfo> server;

    EntityFactory factory;
    EntityCollection entities;

    PhysicsSystem physics;

    Delegate<int, const Host::Packet&> onMessageReceived;
    Delegate<int> onPlayerConnected, onPlayerDisconnected;

    void handleMessage(int id, const Host::Packet& data);
    void handlePlayerConnect(int id);
    void handlePlayerDisconnect(int id);

public:

    GameServer(Global& global);

    void update(float dt);

};