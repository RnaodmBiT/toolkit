#pragma once
#include "component.hpp"

struct ShipInput {
    bool thrust, left, right;
    ShipInput() : thrust(false), left(false), right(false) { }
};

struct ShipControl : public Component {
    ShipInput input;
};
