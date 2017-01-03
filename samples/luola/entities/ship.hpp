#pragma once
#include "../includes.hpp"
#include "../menu/text.hpp"
#include "../player_info.hpp"
#include "projectile_types.hpp"

struct Global;

struct ShipInput {

    bool thrust, left, right, shootPrimary, shootSecondary, keyboard;
    float targetRotation;
    int targetShip;

    ShipInput() :
        thrust(false),
        left(false),
        right(false),
        shootPrimary(false),
        shootSecondary(false),
        keyboard(false),
        targetShip(-1),
        targetRotation(0) { }

};

class Ship {
    Vec2f position, velocity;
    float rotation, drag, mass, primaryReloadTime, secondaryReloadTime;
    ShipInput input;
    Team team;
    int primary;
    int secondary;
    uint8_t owner;
    int health;
    Shape shape;
    Text playerName;
    Shader* shader;
    friend tk::core::convert<Ship>;
public:
    Ship(Global& global, const Vec2f& position, float rotation, Team team, uint8_t owner, Vec4f color);

    void createGraphics();

    void setInput(const ShipInput& input);
    void takeDamage(int damage);

    void update(float dt);
    void draw(const Mat4f& projection);

    Vec2f getDirection() const;
    float getRotation() const;
    Vec2f getPosition() const;
    Vec2f getVelocity() const;
    int getPrimary();
    int getSecondary();
    ShipInput getInput() const;
    int getHealth() const;
    Team getTeam() const;
    uint8_t getOwner() const;

    void thrust(float strength, float dt);
    void rotate(float speed, float dt);
    void force(Vec2f momentum);

    bool canShootPrimary() const;
    bool canShootSecondary() const;
    void resetPrimaryReload();
    void resetSecondaryReload();

    void setPlayerName(const std::string& name);
};

namespace tk {
    namespace core {
        template <>
        struct convert<Ship> {

            void serialize(Blob& blob, const Ship& ship) {
                tk::core::serialize(blob, ship.position, ship.velocity, ship.rotation, ship.input, (uint8_t)ship.team, ship.owner, ship.health, ship.primary, ship.secondary);
            }

            void deserialize(Blob::const_iterator& it, Ship& ship) {
                uint8_t team;
                tk::core::deserialize(it, ship.position, ship.velocity, ship.rotation, ship.input, team, ship.owner, ship.health, ship.primary, ship.secondary);
                ship.team = (Team)team;
            }
        };

        template <>
        struct convert<ShipInput> {
            void serialize(Blob& blob, const ShipInput& input) {
                uint8_t bitfield = (input.thrust ? 1 : 0) | (input.left ? 2 : 0) | (input.right ? 4 : 0) | (input.shootPrimary ? 8 : 0) | (input.shootSecondary ? 16 : 0) | (input.keyboard ? 32 : 0);
                tk::core::serialize(blob, bitfield, input.targetShip, input.targetRotation);
            }

            void deserialize(Blob::const_iterator& it, ShipInput& input) {
                uint8_t bitfield;

                tk::core::deserialize(it, bitfield, input.targetShip, input.targetRotation);
                input.thrust = (bitfield & 1) > 0;
                input.left = (bitfield & 2) > 0;
                input.right = (bitfield & 4) > 0;
                input.shootPrimary = (bitfield & 8) > 0;
                input.shootSecondary = (bitfield & 16) > 0;
                input.keyboard = (bitfield & 32) > 0;
            }
        };
    }
}
