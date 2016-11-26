#pragma once

#include <core.hpp>


struct Global {
    tk::core::ResourceCollection resources;
    tk::core::Keyboard keyboard;
    tk::core::Vec2i resolution;
};

typedef tk::core::State<Global> LuolaState;
