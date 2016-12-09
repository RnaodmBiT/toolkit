#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <net.hpp>

#include "input_manager.hpp"

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

    bool running;

    // Alias to certain variables
    int &width, &height;

    Global() :
        width(settings.resolution.x),
        height(settings.resolution.y),
        running(true) { }

    void quit() {
        running = false;
    }
};


typedef State<Global> GameState;
