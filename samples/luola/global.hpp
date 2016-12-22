#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <net.hpp>
#include <memory>
#include <chrono>

#include "managers/input_manager.hpp"
#include "game_server.hpp"

using namespace tk::core;
using namespace tk::graphics;
using namespace tk::net;

typedef std::chrono::high_resolution_clock Clock;

struct Settings {
    Vec2i resolution;
};

struct Global {
    Settings settings;
    ResourceCollection cache;
    InputManager input;

    std::string playerName;
    std::string remote;
    std::unique_ptr<GameServer> server;

    bool running;

    // Alias to certain variables
    int &width, &height;

    Global() :
        width(settings.resolution.x),
        height(settings.resolution.y),
        running(true),
        remote("localhost") { 
        gameStart = clock.now();
    }

    void quit() {
        running = false;
    }

    float time() {
        Clock::duration delta = clock.now() - gameStart;
        return (float)std::chrono::duration_cast<std::chrono::microseconds>(delta).count() / 1e6f;
    }

private:
    Clock clock;
    Clock::time_point gameStart;
};


typedef State<Global> GameState;
