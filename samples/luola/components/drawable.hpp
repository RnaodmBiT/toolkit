#pragma once
#include "component.hpp"
#include <graphics.hpp>
using namespace tk::graphics;

struct DrawableComponent : public Component {
    Shape shape;
    Shader* shader;
    Texture* texture;

    DrawableComponent(Shape&& shape, Shader* shader, Texture* texture) : 
        shape(std::move(shape)),
        shader(shader),
        texture(texture) { }
};
