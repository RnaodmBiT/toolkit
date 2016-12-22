#pragma once
#include "../global.hpp"
#include "element.hpp"
#include "text.hpp"
#include <map>

class Button : public Element {
    enum State { Up, Over, Down, DownAndOut } state;
    std::map<State, Vec4f> colors;
    Text label;

public:
    std::function<void()> onClick;

    Button(Global& global, const Vec2f& position, const std::string& text, int size) : state(Up) {
        label = Text(global.cache.get<Font>("font"),
                     global.cache.get<Shader>("shader"),
                     position,
                     text, size);

        colors[Down] = { 0.8f, 0.8f, 0.8f, 1.0f };
        colors[Up] = { 0.9f, 0.9f, 0.9f, 1.0f };
        colors[Over] = { 1.0f, 1.0f, 1.0f, 1.0f };
        colors[DownAndOut] = colors[Up];
    }

    void draw(const Mat4f& projection, const Mat4f& transform = Mat4f(), float transparency = 1.0f) {
        label.setColor(colors[state]);
        label.draw(projection, transform, alpha * transparency);
    }

    Vec2f getSize() const {
        return label.getSize();
    }

    Vec2f getPosition() const {
        return label.getPosition();
    }

    void onEnter() {
        if (state == Up) {
            state = Over;
        } else if (state == DownAndOut) {
            state = Down;
        }
    }

    void onLeave() {
        if (state == Over) {
            state = Up;
        } else if (state == Down) {
            state = DownAndOut;
        }
    }

    void onPress(bool inside) {
        if (inside) {
            state = Down;
        }
    }

    void onRelease(bool inside) {
        if (inside && state == Down) {
            onClick();
            state = Over;
        }
        if (!inside) {
            state = Up;
        }
    }
};
