#pragma once

#include <core.hpp>
#include <string>


struct Global {
    tk::core::ResourceCollection resources;
    tk::core::Keyboard keyboard;
    tk::core::Mouse mouse;
    tk::core::Vec2i resolution;
};

typedef tk::core::State<Global> LuolaState;


struct PlayerInfo {
    std::string name;
};