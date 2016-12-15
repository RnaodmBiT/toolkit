#pragma once
#include "../entity.hpp"

class PhysicsSystem {
public:

    void update(float dt, EntityCollection& entities);
};
