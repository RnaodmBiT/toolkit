#pragma once
#include "component.hpp"
#include <core.hpp>
using namespace tk::core;

struct ProjectileComponent : public Component {
	Vec2f velocity;

	ProjectileComponent(const Vec2f& velocity = Vec2f()) : velocity(velocity) { }
};