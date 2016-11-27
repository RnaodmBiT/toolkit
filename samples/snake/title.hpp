#pragma once

#include <core.hpp>
#include <graphics.hpp>
#include <layout.hpp>
#include <memory>

#include "global.hpp"

using namespace tk::core;
using namespace tk::graphics;
using namespace tk::layout;

class Title : public SnakeState {
    Global* global;
    UIFactory uiFactory;

    std::unique_ptr<DrawableNode> scene;
    std::vector<std::unique_ptr<DrawableNode>> menu;

    DrawableNode* createMenuNode(const std::string& name, const json& data);

public:
    void create(Global& global);
    SnakeState* update(float dt);
    void draw();
    void shutdown();
};