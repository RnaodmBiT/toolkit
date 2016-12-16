#pragma once
#include "component.hpp"
#include <core.hpp>
using namespace tk::core;

struct PositionComponent : public Component {
    Vec2f position;
    float rotation;

    PositionComponent(const Vec2f& p, float rotation = 0) : position(p), rotation(rotation) { }
};
