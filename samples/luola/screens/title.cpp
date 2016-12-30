#include "title.hpp"
#include "lobby.hpp"
#include "../menu/cursor.hpp"

Title::Title(Global& global) : 
    GameState(global),
    menu(global),
    join(global),
    host(global),
    options(global),
    background(global),
    tweens(global),
    activePanel(nullptr) {
    title = Text(global.cache.get<Font>("font"),
                 global.cache.get<Shader>("shader"),
                 { 50, 50 },
                 "LUOLA", 50);

    buildMenu();
    Cursor::set(Cursor::Arrow);

    global.input.onMouseUp.attach(onRelease, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseUp();
            if (activePanel) {
                activePanel->mouseUp();
            }
        }
    });

    global.input.onMouseDown.attach(onClick, [&] (int button, Vec2i position) {
        if (button == SDL_BUTTON_LEFT) {
            menu.mouseDown();
            if (activePanel) {
                activePanel->mouseDown();
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
    if (global.server) {
        global.server->update(0.0f);
    }
    if (global.client) {
        global.client->pollEvents();
    }

    tweens.update();

    backgroundPosition.x += dt * 10.0f;
    backgroundPosition.y = -(float)global.height * 0.45f;

    return GameState::update(dt);
}

void Title::shutdown() { }

void Title::draw() {
    Mat4f projection = orthographic(0, 0, (float)global.width, (float)global.height);

    background.draw(projection, backgroundPosition);

    title.draw(projection);
    menu.draw(projection);

    join.draw(projection);
    host.draw(projection);
    options.draw(projection);
}

void Title::buildMenu() {
    buildJoinPanel();
    buildHostPanel();
    buildOptionsPanel();

    menu.addButton("Join", 20)->onClick = [&] () { showPanel(join); };
    menu.addButton("Host", 20)->onClick = [&] () { showPanel(host); };
    menu.addButton("Options", 20)->onClick = [&] () { showPanel(options); };
    menu.addButton("Quit", 20)->onClick = [&] () { global.quit(); };

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
        connectToServer(address->getText(), name->getText());
    };

    join.setAlpha(0);
}

void Title::buildHostPanel() {
    host.create("Host Game", { 170, 150 });

    host.addSpace(20);
    host.addText("> Player Name", 15);
    TextInput* name = host.addTextInput(18);

    host.addSpace(20);
    host.addButton("Start", 20)->onClick = [&, name] () {
        global.server.reset(new GameServer(global));
        connectToServer("127.0.0.1", name->getText());
    };

    host.setAlpha(0);
}

void Title::buildOptionsPanel() {
    options.create("Options", { 170, 150 });
    options.setAlpha(0);
}

void Title::showPanel(Panel& panel) {
    Panel* active = activePanel;

    if (activePanel == &panel) {
        tweens.create(0.2f, Easing::quadraticOut, [=] (float x) {
            active->setAlpha(1 - x); 
        });
        activePanel = nullptr;
    } else {
        if (active) {
            tweens.create(0.2f, Easing::quadraticOut, [=] (float x) { active->setAlpha(1 - x); });
        }
        active = activePanel = &panel;
        tweens.create(0.2f, Easing::quadraticOut, [=] (float x) { active->setAlpha(x); });
    }
}

void Title::connectToServer(const std::string& address, const std::string& name) {
    global.client.reset(new Client<PlayerInfo>());
    global.client->connect(address, 2514, { name });

    global.playerName = name;
    global.remote = address;
    
    global.client->onConnectedToServer.attach(onConnectedToGame, [&] () {
        setNextState(new Lobby(global));
    });
}
