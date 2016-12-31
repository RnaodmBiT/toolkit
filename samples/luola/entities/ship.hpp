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
    Vec2f position, velocity;
    float rotation, drag, mass, reloadTime;
    ShipInput input;
    Team team;
    uint8_t owner;
    Shape shape;
    Text playerName;
    Shader* shader;
    friend tk::core::convert<Ship>;
public:
    Ship(Global& global, const Vec2f& position, float rotation, Team team, uint8_t owner, Vec4f color);

    void setInput(const ShipInput& input);

    void update(float dt);
    void draw(const Mat4f& projection);

    Vec2f getDirection() const;
    float getRotation() const;
    Vec2f getPosition() const;
    Vec2f getVelocity() const;
    ShipInput getInput() const;
    Team getTeam() const;
    uint8_t getOwner() const;

    void thrust(float strength, float dt);
    void rotate(float speed, float dt);

    bool canShoot() const;
    void resetReloadTime();

    void setPlayerName(const std::string& name);
};

namespace tk {
    namespace core {
        template <>
        struct convert<Ship> {
            void serialize(Blob& blob, const Ship& ship) {
                tk::core::serialize(blob, ship.position, ship.velocity, ship.rotation, ship.input, (uint8_t)ship.team, ship.owner);
            }

            void deserialize(Blob::const_iterator& it, Ship& ship) {
                uint8_t team;
                tk::core::deserialize(it, ship.position, ship.velocity, ship.rotation, ship.input, team, ship.owner);
                ship.team = (Team)team;
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
