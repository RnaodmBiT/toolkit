#include "title.hpp"

Title::Title(Global& global) : 
    GameState(global),
    menu(global) {
    title = Text(global.cache.get<Font>("font"),
                 global.cache.get<Shader>("shader"),
                 { 50, 50 },
                 "LUOLA", 50);

    menu.addButton("Play", 20).onClick = [] () {
        tk_info("Play");
    };

    menu.addButton("Quit", 20).onClick = [&] () {
        global.quit();
    };

    menu.setPosition({ 50, (float)global.height - 200 });

    global.input.onMouseUp.attach(onRelease, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseUp(position);
        }
    });

    global.input.onMouseDown.attach(onClick, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseDown(position);
        }
    });

    global.input.onMouseMove.attach(onMove, [&] (Vec2i position) {
        menu.mouseMove(position);
    });
}

GameState* Title::update(float dt) {
    return GameState::update(dt);
}

void Title::shutdown() { }

void Title::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    title.draw(projection);
    menu.draw(projection);
}
