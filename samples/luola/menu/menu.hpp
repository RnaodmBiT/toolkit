#pragma once
#include "../global.hpp"
#include "button.hpp"

class Menu {
    Global& global;
    std::vector<Button> buttons;
    struct Colors { Vec4f up, over, down; } colors;
    Vec2f position, offset;
    float spacing;

public:

    Menu(Global& global, float spacing = 20) : global(global), spacing(spacing) {
        colors.down = { 0.5f, 0.5f, 0.5f, 1.0f };
        colors.up = { 0.7f, 0.7f, 0.7f, 1.0f };
        colors.over = { 1.0f, 1.0f, 1.0f, 1.0f };
    }

    Button& addButton(const std::string& label, int size) {
        buttons.emplace_back();
        Button& btn = buttons[buttons.size() - 1];

        btn.label = Text(global.cache.get<Font>("font"),
                         global.cache.get<Shader>("shader"),
                         offset,
                         label, size);

        offset.y += btn.label.getSize().y + spacing;
        return btn;
    }

    void setPosition(const Vec2f& pos) {
        position = pos;
    }

    void mouseMove(Vec2i mouse) {
        Vec2f p = Vec2f{ (float)mouse.x, (float)mouse.y } -position;
        for (Button& btn : buttons) {
            if (btn.isInside(p)) {
                if (btn.state == Button::Up) {
                    btn.state = Button::Over;
                } else if (btn.state == Button::DownAndOut) {
                    btn.state = Button::Down;
                }
            } else {
                if (btn.state == Button::Down) {
                    btn.state = Button::DownAndOut;
                } else if (btn.state == Button::Over) {
                    btn.state = Button::Up;
                }
            }
            
        }
    }

    void mouseDown(Vec2i mouse) {
        Vec2f p = Vec2f{ (float)mouse.x, (float)mouse.y } -position;
        for (Button& btn : buttons) {
            if (btn.isInside(p)) {
                btn.state = Button::Down;
            }
        }
    }

    void mouseUp(Vec2i mouse) {
        Vec2f p = Vec2f{ (float)mouse.x, (float)mouse.y } - position;
        for (Button& btn : buttons) {
            if (btn.isInside(p)) {
                btn.onClick();
                btn.state = Button::Over;
            } else {
                btn.state = Button::Up;
            }
        }
    }

    void draw(const Mat4f& projection) {
        Mat4f proj = projection * translate(position.x, position.y, 0.0f);
        for (Button& btn : buttons) {
            switch (btn.state) {
            case Button::Up:
            case Button::DownAndOut:
                btn.label.setColor(colors.up);
                break;
            case Button::Over:
                btn.label.setColor(colors.over);
                break;
            case Button::Down:
                btn.label.setColor(colors.down);
                break;
            }
            btn.label.draw(proj);
        }
    }
};