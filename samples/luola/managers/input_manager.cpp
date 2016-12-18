#include "input_manager.hpp"

void InputManager::handleKeyboard(int key, bool press) {
    keys[key] = press;
}

void InputManager::handleMouse(int button, bool press) {
    buttons[button] = press;
    if (press) {
        onMouseDown(button, mousePosition);
    } else {
        onMouseUp(button, mousePosition);
    }
}

void InputManager::handleMotion(int x, int y) {
    mousePosition = { x, y };
    onMouseMove(mousePosition);
}

const Vec2i& InputManager::getMousePosition() const {
    return mousePosition;
}

bool InputManager::isKeyDown(int key) const {
    return keys.count(key) && keys.at(key);
}

bool InputManager::isButtonDown(int button) const {
    return buttons.count(button) && buttons.at(button);
}
