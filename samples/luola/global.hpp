#pragma once
#include "includes.hpp"
#include "managers/input_manager.hpp"
#include "game_server.hpp"

struct Settings {
    Vec2i resolution;
};

struct Global {
    Settings settings;
    ResourceCollection cache;
    InputManager input;

    std::string playerName;
    std::string remote;
    std::unique_ptr<GameServer> server;
    std::unique_ptr<Client<PlayerInfo>> client;

    bool running;

    // Alias to certain variables
    int &width, &height;

    Global() :
        width(settings.resolution.x),
        height(settings.resolution.y),
        running(true),
        remote("localhost") { 
        gameStart = clock.now();
    }

    void quit() {
        running = false;
    }

    void updateNetwork(float dt) {
        if (server) {
            server->update(dt);
        }
        if (client) {
            client->pollEvents();
        }
    }

    float time() {
        Clock::duration delta = clock.now() - gameStart;
        return (float)std::chrono::duration_cast<std::chrono::microseconds>(delta).count() / 1e6f;
    }

private:
    Clock clock;
    Clock::time_point gameStart;
};


typedef State<Global> GameState;
