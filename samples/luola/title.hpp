#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"
#include "button.hpp"

class Title : public LuolaState {
    std::unique_ptr<DrawableNode> scene;
    std::unique_ptr<InputNode> input;

    std::unique_ptr<Button> quit;
    Delegate<> quitHandler;

    std::unique_ptr<TextNode> title, instructions;

    Delegate<int> keyPress, mouseRelease;
    Delegate<> connectedToServer;

public:
    Title(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
