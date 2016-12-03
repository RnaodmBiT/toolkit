#pragma once
#include <core.hpp>
#include <net.hpp>

#include "player_info.hpp"
#include "ship.hpp"

using namespace tk::core;
using namespace tk::net;


class GameServer {
    Server<PlayerInfo> server;
    std::vector<Ship> ships;

    Delegate<int> onConnect, onDisconnect;
    Delegate<int, const Host::Packet&> onReceive;

    UpdateTimer networkTick;

    void spawnShip(int player, Vec2f position, Vec4f color);
    void deleteShip(int player);

public:

    GameServer();

    void startServer(int port);
    void update(float dt);
};