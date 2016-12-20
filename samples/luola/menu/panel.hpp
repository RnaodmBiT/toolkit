#pragma once
#include "../global.hpp"
#include "element.hpp"
#include "text.hpp"
#include "button.hpp"
#include "textInput.hpp"
#include <memory>

class Panel {
    Global& global;
    Shape background;
    Vec2f position;
    Vec4f color;

    Vec2f offset;
    float spacing;

    Text title;
    std::vector<std::unique_ptr<Element>> elements;

    Shader* shader;
public:

    Panel(Global& global) : shader(nullptr), global(global), spacing(5) { }

    void create(const std::string& heading, const Vec2f& pos) {
        position = pos;
        shader = global.cache.get<Shader>("shader");
        background = Shape::rectangle(Vec2f(), { (float)global.width - position.x - 50,
                                                 (float)global.height - position.y - 50 });
        color = { 0.03f, 0.03f, 0.03f, 1.0f };
        title = Text(global.cache.get<Font>("font"), shader,
                     { 20, 20 }, heading, 30);

        offset = { 20, 70 };
    }

    void draw(const Mat4f& projection) {
        Mat4f transform = projection * translate(position.x, position.y, 0.0f);
        shader->apply();
        shader->setUniform("transform", transform);
        shader->setUniform("tint", color);
        shader->clearTexture("image");
        background.draw();

        title.draw(transform);

        for (auto& element : elements) {
            element->draw(transform);
        }
    }

    Button* addButton(const std::string& label, int size) {
        elements.emplace_back(new Button(global, offset, label, size));
        offset.y += elements.back()->getSize().y + spacing;
        return (Button*)elements.back().get();
    }

    Text* addText(const std::string& label, int size) {
        Font* font = global.cache.get<Font>("font");
        Shader* shader = global.cache.get<Shader>("shader");
        elements.emplace_back(new Text(font, shader, offset, label, size));
        offset.y += elements.back()->getSize().y + spacing;
        return (Text*)elements.back().get();
    }

    TextInput* addTextInput(int size) {
        elements.emplace_back(new TextInput(global, offset, size));
        offset.y += elements.back()->getSize().y + spacing;
        return (TextInput*)elements.back().get();
    }

    void addSpace(float size) {
        offset.y += size;
    }

    void mouseMove(Vec2f mouse) {
        mouse -= position;
        for (auto& element : elements) {
            element->mouseMove(mouse);
        }
    }

    void mouseDown(Vec2f mouse) {
        mouse -= position;
        for (auto& element : elements) {
            element->mouseDown(mouse);
        }
    }

    void mouseUp(Vec2f mouse) {
        mouse -= position;
        for (auto& element : elements) {
            element->mouseUp(mouse);
        }
    }
};