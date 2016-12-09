#pragma once
#include "component.hpp"
#include <core.hpp>
using namespace tk::core;

struct PositionComponent : public Component {
    Vec2f position;

    PositionComponent(const Vec2f& p) : position(p) { }
};
