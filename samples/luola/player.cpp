#include "controller.hpp"
#include "SDL.h"

PlayerController::PlayerController(Global& global, Ship& ship) : Controller(ship), input(Keyboard) {
    inputToggle.event = [this] (int key) {
        if (key == SDLK_SPACE) {
            if (input == Keyboard) {
                input = Mouse;
            } else {
                input = Keyboard;
            }
        }
    };
    global.keyboard.keyPress.attach(inputToggle);
}

void PlayerController::update(Global& global, float dt) {
    if (global.keyboard.isKeyDown(SDLK_w)) {
        ship.applyThrust(500, dt);
    }

    if (input == Keyboard) {
        if (global.keyboard.isKeyDown(SDLK_a)) {
            ship.rotate(-4, dt);
        }
        if (global.keyboard.isKeyDown(SDLK_d)) {
            ship.rotate(4, dt);
        }
    } else {
        float angle = std::atan2((float)global.mouse.y - ship.getPosition().y, (float)global.mouse.x - ship.getPosition().x);
        float delta = wrapAngle(angle - ship.getAngle()) / dt;

        if (std::abs(delta) > 4) {
            delta = sign(delta) * 4;
        }
        ship.rotate(delta, dt);
    }
}