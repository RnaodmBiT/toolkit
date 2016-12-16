#pragma once

#include "global.hpp"
#include "entity.hpp"
#include "systems/physics.hpp"
#include "systems/rendering.hpp"
#include "types.hpp"


class Playground : public GameState {
    Client<PlayerInfo> client;

    EntityCollection entities;
    EntityFactory factory;

    PhysicsSystem physics;
    RenderingSystem rendering;

    Delegate<const Host::Packet&> onMessageReceived;

    void handleMessage(const Host::Packet& data);
    void handleCreateEntity(Host::Packet::const_iterator& it);

public:

    Playground(Global& global);

    GameState* update(float dt);
    void shutdown();
    void draw();

};
