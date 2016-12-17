#include "title.hpp"

Title::Title(Global& global) : GameState(global) {
    title = Text(global.cache.get<Font>("font"),
                 global.cache.get<Shader>("shader"),
                 { 50, 50 },
                 "LUOLA", 50);
}

GameState* Title::update(float dt) {
    return GameState::update(dt);
}

void Title::shutdown() { }

void Title::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    title.draw(projection);
}
