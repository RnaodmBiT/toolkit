#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <net.hpp>
#include <memory>

#include "managers/input_manager.hpp"
#include "game_server.hpp"

using namespace tk::core;
using namespace tk::graphics;
using namespace tk::net;

struct Settings {
    Vec2i resolution;
};

struct Global {
    Settings settings;
    ResourceCollection cache;
    InputManager input;

    std::string remote;
    std::unique_ptr<GameServer> server;

    bool running;

    // Alias to certain variables
    int &width, &height;

    Global() :
        width(settings.resolution.x),
        height(settings.resolution.y),
        running(true),
        remote("localhost") { }

    void quit() {
        running = false;
    }
};


typedef State<Global> GameState;
