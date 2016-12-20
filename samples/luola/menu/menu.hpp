#pragma once
#include "../global.hpp"
#include "button.hpp"

class Menu {
    Global& global;
    std::vector<Button> buttons;
    Vec2f position, offset;
    float spacing;

public:

    Menu(Global& global, float spacing = 20) : global(global), spacing(spacing) { }

    Button* addButton(const std::string& label, int size) {
        buttons.emplace_back(global, offset, label, size);
        Button* button = &buttons[buttons.size() - 1];
        offset.y += button->getSize().y + spacing;
        return button;
    }

    void setPosition(const Vec2f& pos) {
        position = pos;
    }

    void mouseMove(Vec2f mouse) {
        mouse -= position;
        for (Button& button : buttons) {
            button.mouseMove(mouse);
        }
    }

    void mouseDown(Vec2f mouse) {
        mouse -= position;
        for (Button& button : buttons) {
            button.mouseDown();
        }
    }

    void mouseUp(Vec2f mouse) {
        mouse -= position;
        for (Button& button : buttons) {
            button.mouseUp();
        }
    }

    void draw(const Mat4f& projection) {
        Mat4f proj = projection * translate(position.x, position.y, 0.0f);
        for (Button& button : buttons) {
            button.draw(proj);
        }
    }

    Vec2f getSize() {
        Vec2f size;
        for (Button& btn : buttons) {
            Vec2f bottomRight= btn.getPosition() + btn.getSize();
            size.x = std::max(size.x, bottomRight.x);
            size.y = std::max(size.y, bottomRight.y);
        }
        return size;
    }
};