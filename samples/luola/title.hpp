#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;

class Title : public LuolaState {
    std::unique_ptr<DrawableNode> scene;

    std::unique_ptr<TextNode> title;

    Delegate<int> keyPress;

public:
    Title(Global& global);
    LuolaState* update(float dt);
    void draw();
    void shutdown();
};
