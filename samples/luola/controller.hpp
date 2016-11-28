#pragma once
#include "global.hpp"
#include "ship.hpp"

class Controller {
protected:
    Ship& ship;
public:
    Controller(Ship& ship) : ship(ship) { }
    virtual ~Controller() { }
    virtual void update(Global& global, float dt) = 0;
};


class PlayerController : public Controller {
public:
    PlayerController(Ship& ship);
    void update(Global& global, float dt);
};