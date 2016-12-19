#include "input_manager.hpp"

void InputManager::handleKeyboard(int key, bool press) {
    keys[key] = press;
    if (press) {
        onKeyDown(key);
    } else {
        onKeyUp(key);
    }
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

void InputManager::handleText(std::string text) {
    onTextInput(text);
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
