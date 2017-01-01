#pragma once
#include "../includes.hpp"
#include "../menu/text.hpp"
#include "../player_info.hpp"

struct Global;

struct ShipInput {

    bool thrust, left, right, shoot, keyboard;
    float targetRotation;

    ShipInput() :
        thrust(false),
        left(false),
        right(false),
        shoot(false),
        keyboard(false),
        targetRotation(0) { }

};

class Ship {
    Global& global;

    // The current state of the ship, used for general calculations and rendering
    struct State {
        Vec2f position, velocity;
        float rotation;
        ShipInput input;
    } state;

    // Client side prediction variables
    float clientTruthTime;
    State clientTruth;
    std::vector<std::pair<float, ShipInput>> clientInputs;

    // Ship properties that dont need client side prediction
    float drag, mass, reloadTime;
    int health;

    Team team;
    uint8_t owner;

    // Graphics members
    Shape shape;
    Text playerName;
    Shader* shader;

    void clearOldClientInputs();

    friend tk::core::convert<Ship>;
public:
    Ship(Global& global, const Vec2f& position, float rotation, Team team, uint8_t owner, Vec4f color);

    void createGraphics();

    void setInput(const ShipInput& input);
    void setClientInput(const ShipInput& input);

    void serverUpdate(float dt);
    void clientUpdate(float dt);

    void draw(const Mat4f& projection);

    Vec2f getDirection() const;
    float getRotation() const;
    Vec2f getPosition() const;
    Vec2f getVelocity() const;
    ShipInput getInput() const;
    int getHealth() const;
    Team getTeam() const;
    uint8_t getOwner() const;

    void thrust(float strength, float dt);
    void rotate(float speed, float dt);

    void takeDamage(int damage);

    bool canShoot() const;
    void resetReloadTime();

    void setPlayerName(const std::string& name);
};

namespace tk {
    namespace core {
        template <>
        struct convert<Ship> {

            void serialize(Blob& blob, const Ship& ship) {
                tk::core::serialize(blob, 
                                    ship.state.position,
                                    ship.state.velocity,
                                    ship.state.rotation,
                                    ship.state.input,
                                    (uint8_t)ship.team,
                                    ship.owner,
                                    ship.health);
            }

            void deserialize(Blob::const_iterator& it, Ship& ship) {
                uint8_t team;
                tk::core::deserialize(it, 
                                      ship.clientTruth.position,
                                      ship.clientTruth.velocity,
                                      ship.clientTruth.rotation,
                                      ship.clientTruth.input,
                                      team,
                                      ship.owner,
                                      ship.health);
                ship.team = (Team)team;
                ship.clearOldClientInputs();
            }
        };

        template <>
        struct convert<ShipInput> {
            void serialize(Blob& blob, const ShipInput& input) {
                uint8_t bitfield = (input.thrust ? 1 : 0) | (input.left ? 2 : 0) | (input.right ? 4 : 0) | (input.shoot ? 8 : 0) | (input.keyboard ? 16 : 0);
                tk::core::serialize(blob, bitfield, input.targetRotation);
            }

            void deserialize(Blob::const_iterator& it, ShipInput& input) {
                uint8_t bitfield;

                tk::core::deserialize(it, bitfield, input.targetRotation);
                input.thrust = (bitfield & 1) > 0;
                input.left = (bitfield & 2) > 0;
                input.right = (bitfield & 4) > 0;
                input.shoot = (bitfield & 8) > 0;
                input.keyboard = (bitfield & 16) > 0;
            }
        };
    }
}
