#include "controller.hpp"
#include "SDL.h"

PlayerController::PlayerController(Ship& ship) : Controller(ship) { }

void PlayerController::update(Global& global, float dt) {
    if (global.keyboard.isKeyDown(SDLK_w)) {
        ship.applyThrust(500, dt);
    }
    if (global.keyboard.isKeyDown(SDLK_a)) {
        ship.rotate(4, dt);
    }
    if (global.keyboard.isKeyDown(SDLK_d)) {
        ship.rotate(-4, dt);
    }
}