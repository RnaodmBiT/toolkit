#pragma once
#include "../entity.hpp"

class RenderingSystem {
public:
    void render(EntityCollection& entities, const Mat4f& transform);
};
