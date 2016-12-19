#pragma once
#include "../global.hpp"
#include "element.hpp"
#include "text.hpp"

class TextInput : public Element {
    Shader* shader;
    Text text;
    Shape background;
    Vec2f position;
    int size;

    std::string field;
    Delegate<int> onKeyDown;
    Delegate<const std::string&> onTextInput;

    struct Colors { Vec4f off, over, active; } colors;
    enum State { Off, Over, Active, ActiveAndOver } state;

public:
    TextInput() { }

    TextInput(Global& global, const Vec2f& position, int size) : 
        position(position), size(size), state(Off) {
        shader = global.cache.get<Shader>("shader");
        text = Text(global.cache.get<Font>("font"),
                    shader, Vec2f{ 2, -2 }, "", size);
        text.setColor({ 0, 0, 0, 1 });
        background = Shape::rectangle({ 0, 0 }, { 200, (float)size + 2 });

        colors.off= { 0.5f, 0.5f, 0.5f, 1.0f };
        colors.active = { 0.7f, 0.7f, 0.7f, 1.0f };
        colors.over = { 1.0f, 1.0f, 1.0f, 1.0f };

        global.input.onTextInput.attach(onTextInput, [&] (const std::string& text) {
            if (isActive()) {
                field += text;
            }
        });

        global.input.onKeyDown.attach(onKeyDown, [&] (int key) {
            if (key == SDLK_BACKSPACE && isActive() && field.size()) {
                field = field.substr(0, field.size() - 1);
            }
        });

    }

    void setPosition(const Vec2f& pos) {
        position = pos;
    }

    Vec2f getPosition() const {
        return position;
    }

    Vec2f getSize() const {
        return{ 200, (float)size + 2 };
    }

    void draw(const Mat4f& projection) {
        if (shader) {
            Mat4f transform = projection * translate(position.x, position.y, 0.0f);

            std::string display = field;
            Vec4f color;
            switch (state) {
            case Active:
                color = colors.active;
                break;
            case Over:
            case ActiveAndOver:
                color = colors.over;
                break;
            default:
                color = colors.off;
                break;
            }

            if (isActive()) {
                display += "_";
            }

            shader->apply();
            shader->setUniform("transform", transform);
            shader->setUniform("tint", color);
            shader->clearTexture("image");
            background.draw();

            text.setText(display, size);
            text.draw(transform);
        }
    }

    void mouseMove(Vec2f mouse) {
        if (isInside(mouse)) {
            if (state == Active) {
                state = ActiveAndOver;
            } else if (state == Off) {
                state = Over;
            }
        } else {
            if (state == ActiveAndOver) {
                state = Active;
            } else if (state == Over) {
                state = Off;
            }
        }

    }

    void mouseDown(Vec2f mouse) {
        if (state == Over) {
            state = ActiveAndOver;
            SDL_StartTextInput();
        }
    }

    void mouseUp(Vec2f mouse) {
        if (state == Active) {
            state = Off;
            SDL_StopTextInput();
        }
    }

    bool isActive() const {
        return state == Active || state == ActiveAndOver;
    }
};