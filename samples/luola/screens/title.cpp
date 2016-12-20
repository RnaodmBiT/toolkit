#include "title.hpp"
#include "playground.hpp"

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

    join.addSpace(20);
    join.addText("> Player Name", 15);
    TextInput* name = join.addTextInput(18);

    join.addSpace(20);
    join.addText("> Host Address", 15);
    TextInput* address = join.addTextInput(18);

    join.addSpace(20);
    join.addButton("Connect", 20)->onClick = [&, name, address] () {
        global.playerName = name->getText();
        global.remote = address->getText();
        setNextState(new Playground(global));
    };
}

void Title::buildHostPanel() {
    host.create("Host Game", { 170, 150 });

    host.addSpace(20);
    host.addText("> Player Name", 15);
    TextInput* name = host.addTextInput(18);

    host.addSpace(20);
    host.addButton("Start", 20)->onClick = [&, name] () {
        global.playerName = name->getText();
        global.remote = "127.0.0.1";

        global.server.reset(new GameServer(global));
        setNextState(new Playground(global));
    };
}

void Title::buildOptionsPanel() {
    options.create("Options", { 170, 150 });
}
