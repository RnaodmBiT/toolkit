#pragma once

#include <memory>

struct Component {
    virtual ~Component() { }
};
typedef std::unique_ptr<Component> ComponentPtr;
