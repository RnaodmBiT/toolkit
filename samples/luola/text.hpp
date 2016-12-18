#pragma once
#include "global.hpp"

class Text {
    Font* font;
    Shader* shader;
    Texture texture;
    Shape shape;
    std::string cachedText;

    Vec4f color;
    Vec2f position, bounds;
public:
    Text() : font(nullptr), shader(nullptr), texture(GL_TEXTURE_2D), color{ 1, 1, 1, 1 } { }

    Text(Font* font, Shader* shader, const Vec2f& position, const std::string& text, int size) :
        font(font), shader(shader), position(position), texture(GL_TEXTURE_2D), color{ 1, 1, 1, 1 } {
        setText(text, size);
        texture.useRedAsAlpha();
    }

    void setPosition(const Vec2f& pos) {
        position = pos;
    }

    const Vec2f& getPosition() const {
        return position;
    }

    const Vec2f& getSize() const {
        return bounds;
    }

    void setColor(const Vec4f& c) {
        color = c;
    }

    void setText(const std::string& text, int size) {
        if (cachedText != text && font) {
            cachedText = text;
            Bitmap<uint8_t> image = font->renderText(text, size);
            bounds = Vec2f{ (float)image.getWidth(), (float)image.getHeight() };
            shape = Shape::rectangle({ 0, 0 }, bounds);
            texture.setData(image.getData(), image.getWidth(), image.getHeight(), GL_R8, GL_RED, GL_UNSIGNED_BYTE);
        }
    }

    void draw(const Mat4f& projection) {
        if (shader) {
            shader->apply();
            shader->setUniform("transform", projection * translate(position.x, position.y, 0.0f));
            shader->setUniform("image", texture);
            shader->setUniform("tint", color);
            shape.draw();
        }
    }
};