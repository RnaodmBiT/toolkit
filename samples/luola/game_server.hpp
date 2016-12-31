#pragma once
#include "includes.hpp"
#include "player_info.hpp"
#include "managers/ship_manager.hpp"
#include "managers/projectile_manager.hpp"


struct Global;

class GameServer {
    Global& global;

    bool inProgress;

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
    void handlePlayerChangeTeam(int id);

    Team getAppropriateTeam();

    void shootBullets();
    void spawnShip(int player, Vec2f position);

public:

    GameServer(Global& global);
    ~GameServer();

    void update(float dt);

    void startGame();

};