#pragma once

#include <core.hpp>


struct Global {
    tk::core::ResourceCollection resources;
    tk::core::Keyboard keyboard;
};

typedef tk::core::State<Global> LuolaState;
