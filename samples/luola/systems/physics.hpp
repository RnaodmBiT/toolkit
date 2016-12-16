#pragma once
#include "../entity.hpp"

class PhysicsSystem {

    void updatePhysics(float dt, EntityCollection& entities);
    void updateShipInput(float dt, EntityCollection& entities);
public:

    void update(float dt, EntityCollection& entities);
};
