#pragma once
#include "../global.hpp"
#include <vector>

class Background {
    Global& global;
    Shape shape;
    Shader* shader;
    std::vector<Texture*> layers;
    std::vector<Vec2f> scales;
public:
    Background(Global& global);

    void draw(const Mat4f& projection, const Vec2f& position);
};