#pragma once

#include "player_info.hpp"
#include "game_server.hpp"

#include <core.hpp>
#include <graphics.hpp>
#include <net.hpp>
#include <string>
#include <memory>


using namespace tk::core;
using namespace tk::graphics;
using namespace tk::net;


struct Global {
    ResourceCollection resources;
    Keyboard keyboard;
    Mouse mouse;
    Vec2i resolution;
    Client<PlayerInfo> client;
    GameServer server;
    bool isHost;
};

typedef State<Global> LuolaState;
