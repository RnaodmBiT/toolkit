#pragma once
#include <SDL.h>
#include <core.hpp>

#include <map>

using namespace tk::core;

class InputManager {
    std::map<int, bool> keys, buttons;
    Vec2i mousePosition;

public:


    // Handle input events from the OS
    void handleKeyboard(int key, bool press);
    void handleMouse(int button, bool press);
    void handleMotion(int x, int y);

    const Vec2i& getMousePosition() const;

    bool isKeyDown(int key) const;
    bool isButtonDown(int button) const;
};
