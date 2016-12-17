#pragma once
#include "component.hpp"
#include <core.hpp>
using namespace tk::core;

struct PhysicsComponent : public Component {
    Vec2f velocity;

    PhysicsComponent(const Vec2f& velocity = Vec2f()) : velocity(velocity) { }

};