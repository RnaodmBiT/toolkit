#pragma once
#include "../global.hpp"
#include "element.hpp"
#include "text.hpp"
#include "cursor.hpp"

class TextInput : public Element {
    Shader* shader;
    Text text;
    Shape background;
    Vec2f position;
    int size;

    std::string field;
    Delegate<int> onKeyDown;
    Delegate<const std::string&> onTextInput;

    enum State { Off, Over, Down, DownAndOut, Active, ActiveAndOut } state;
    std::map<State, Vec4f> colors;

public:
    TextInput() { }

    TextInput(Global& global, const Vec2f& position, int size) : 
        position(position), size(size), state(Off) {
        shader = global.cache.get<Shader>("shader");
        text = Text(global.cache.get<Font>("font"),
                    shader, Vec2f{ 2, -2 }, "", size);
        text.setColor({ 0, 0, 0, 1 });
        background = Shape::rectangle({ 0, 0 }, { 200, (float)size + 2 });

        colors[Off] = { 0.5f, 0.5f, 0.5f, 1.0f };
        colors[Active] = { 0.7f, 0.7f, 0.7f, 1.0f };
        colors[Over] = { 1.0f, 1.0f, 1.0f, 1.0f };
        colors[Down] = { 0.3f, 0.3f, 0.3f, 1.0f };
        colors[ActiveAndOut] = colors[Active];
        colors[DownAndOut] = colors[Off];

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

    const std::string& getText() const {
        return field;
    }

    void draw(const Mat4f& projection, const Mat4f& transform = Mat4f()) {
        if (shader) {
            Mat4f trans = transform * translate(position.x, position.y, 0.0f);

            std::string display = field;

            if (isActive()) {
                display += "_";
            }

            Vec4f transformedPosition = trans * Vec4f{ 0, 0, 0, 1 };
            clipRectangle({ transformedPosition.x, transformedPosition.y }, getSize());

            shader->apply();
            shader->setUniform("transform", projection * trans);
            shader->setUniform("tint", colors[state]);
            shader->clearTexture("image");
            background.draw();

            text.setText(display, size);
            text.draw(projection, trans);

            clearClip();
        }
    }

    bool isActive() const {
        return state == Active || state == ActiveAndOut;
    }

    void onEnter() {
        if (state == Off) {
            state = Over;
        } else if (state == ActiveAndOut) {
            state = Active;
        } else if (state == DownAndOut) {
            state = Down;
        }
        Cursor::set(Cursor::IBeam);
    }

    void onLeave() {
        if (state == Over) {
            state = Off;
        } else if (state == Active) {
            state = ActiveAndOut;
        } else if (state == Down) {
            state = DownAndOut;
        }
        Cursor::set(Cursor::Arrow);
    }

    void onPress(bool inside) {
        if (inside) {
            state = Down;
        }
    }

    void onRelease(bool inside) {
        if (state == Down) {
            state = Active;
        } else {
            state = Off;
        }
    }
};