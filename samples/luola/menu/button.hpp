#include "../global.hpp"
#include "element.hpp"
#include "text.hpp"

class Button : public Element {
    enum State { Up, Over, Down, DownAndOut } state;
    struct Colors { Vec4f up, over, down; } colors;
    Text label;

public:
    std::function<void()> onClick;

    Button(Global& global, const Vec2f& position, const std::string& text, int size) : state(Up) {
        label = Text(global.cache.get<Font>("font"),
                     global.cache.get<Shader>("shader"),
                     position,
                     text, size);

        colors.down = { 0.5f, 0.5f, 0.5f, 1.0f };
        colors.up = { 0.7f, 0.7f, 0.7f, 1.0f };
        colors.over = { 1.0f, 1.0f, 1.0f, 1.0f };
    }

    void mouseMove(Vec2f mouse) {
        if (isInside(mouse)) {
            if (state == Button::Up) {
                state = Button::Over;
            } else if (state == Button::DownAndOut) {
                state = Button::Down;
            }
        } else {
            if (state == Button::Down) {
                state = Button::DownAndOut;
            } else if (state == Button::Over) {
                state = Button::Up;
            }
        }

    }

    void mouseDown(Vec2f mouse) {
        if (isInside(mouse)) {
            state = Button::Down;
        }
    }

    void mouseUp(Vec2f mouse) {
        if (state == Button::Down) {
            if (onClick) {
                onClick();
            }
            state = Button::Over;
        }
    }

    void draw(const Mat4f& projection) {
        switch (state) {
        case Button::Up:
        case Button::DownAndOut:
            label.setColor(colors.up);
            break;
        case Button::Over:
            label.setColor(colors.over);
            break;
        case Button::Down:
            label.setColor(colors.down);
            break;
        }
        label.draw(projection);
    }

    Vec2f getSize() const {
        return label.getSize();
    }

    Vec2f getPosition() const {
        return label.getPosition();
    }
};
