#pragma once

#include "global.hpp"

class Button : public InputNode {
    std::unique_ptr<DrawableNode> drawable;
public:
    Button(const std::string& name, const Vec2f& position, DrawableNode* node) : 
        InputNode(name, position, node->getSize()), 
        drawable(node) {
        drawable->setTransform(translate(position.x, position.y, 0.0f));
    }

    DrawableNode* getNode() const {
        return drawable.get();
    }
};