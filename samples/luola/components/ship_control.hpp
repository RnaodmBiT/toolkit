#pragma once
#include "component.hpp"

struct ShipInput {
    bool thrust, left, right, firing;
    ShipInput() : thrust(false), left(false), right(false), firing(false) { }
};

struct ShipControl : public Component {
    ShipInput input;
};
