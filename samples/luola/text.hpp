#pragma once
#include "global.hpp"

class Text {
    Font* font;
    Shader* shader;
    Texture texture;
    Shape shape;
    std::string cachedText;

    Vec2f position;
public:
    Text() : font(nullptr), shader(nullptr), texture(GL_TEXTURE_2D) { }

    Text(Font* font, Shader* shader, const Vec2f& position, const std::string& text, int size) :
        font(font), shader(shader), position(position), texture(GL_TEXTURE_2D) {
        setText(text, size);
        texture.useRedAsAlpha();
    }

    void setText(const std::string& text, int size) {
        if (cachedText != text && font) {
            cachedText = text;
            Bitmap<uint8_t> image = font->renderText(text, size);

            shape = Shape::rectangle({ 0, 0 }, { (float)image.getWidth(), (float)image.getHeight() });
            texture.setData(image.getData(), image.getWidth(), image.getHeight(), GL_R8, GL_RED, GL_UNSIGNED_BYTE);
        }
    }

    void draw(const Mat4f& projection) {
        if (shader) {
            shader->apply();
            shader->setUniform("transform", projection * translate(position.x, position.y, 0.0f));
            shader->setUniform("image", texture);
            shape.draw();
        }
    }
};