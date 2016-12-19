#include "title.hpp"

Title::Title(Global& global) : 
    GameState(global),
    menu(global),
    join(global),
    host(global),
    options(global),
    activePanel(nullptr) {
    title = Text(global.cache.get<Font>("font"),
                 global.cache.get<Shader>("shader"),
                 { 50, 50 },
                 "LUOLA", 50);

    buildMenu();

    global.input.onMouseUp.attach(onRelease, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseUp({ (float)position.x, (float)position.y });
            if (activePanel) {
                activePanel->mouseUp({ (float)position.x, (float)position.y });
            }
        }
    });

    global.input.onMouseDown.attach(onClick, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseDown({ (float)position.x, (float)position.y });
            if (activePanel) {
                activePanel->mouseDown({ (float)position.x, (float)position.y });
            }
        }
    });

    global.input.onMouseMove.attach(onMove, [&] (Vec2i position) {
        menu.mouseMove({ (float)position.x, (float)position.y });
        if (activePanel) {
            activePanel->mouseMove({ (float)position.x, (float)position.y });
        }
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

    if (activePanel) {
        activePanel->draw(projection);
    }
}

void Title::buildMenu() {
    buildJoinPanel();
    buildHostPanel();
    buildOptionsPanel();

    menu.addButton("Join", 20)->onClick = [&] () {
        activePanel = activePanel == &join ? nullptr : &join;
    };

    menu.addButton("Host", 20)->onClick = [&] () {
        activePanel = activePanel == &host ? nullptr : &host;
    };

    menu.addButton("Options", 20)->onClick = [&] () {
        activePanel = activePanel == &options ? nullptr : &options;
    };

    menu.addButton("Quit", 20)->onClick = [&] () {
        global.quit();
    };

    menu.setPosition({ 50, (float)global.height - 50 - menu.getSize().y });
}

void Title::buildJoinPanel() {
    join.create("Join Game", { 170, 150 });
    join.addText(">This is text<", 15);
    join.addButton("THINGY", 20);
}

void Title::buildHostPanel() {
    host.create("Host Game", { 170, 150 });
}

void Title::buildOptionsPanel() {
    options.create("Options", { 170, 150 });
}
