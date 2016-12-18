#pragma once
#include <core.hpp>
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

struct Global;

struct ShipInput {
    bool thrust, left, right, shoot, mode;
    float target_rotation;

    ShipInput() :
        thrust(false),
        left(false),
        right(false),
        shoot(false),
        mode(false)
    { }
};

class Ship {
    Vec2f position, velocity;
    float rotation, drag, mass, reloadTime;
    ShipInput input;

    Shape shape;
    Shader* shader;
    friend tk::core::convert<Ship>;
public:
    Ship(Global& global, const Vec2f& position, float rotation, Vec4f color);

    void setInput(const ShipInput& input);

    void update(float dt);
    void render(const Mat4f& projection);

    Mat4f getTransform() const;
    Vec2f getDirection() const;
    float getRotation() const;
    Vec2f getPosition() const;
    Vec2f getVelocity() const;
    ShipInput getInput() const;

    void thrust(float strength, float dt);
    void rotate(float speed, float dt);

    bool canShoot() const;
    void resetReloadTime();
};

namespace tk {
    namespace core {
        template <>
        struct convert<Ship> {
            void serialize(Blob& blob, const Ship& ship) {
                tk::core::serialize(blob, ship.position, ship.velocity, ship.rotation, ship.input);
            }

            void deserialize(Blob::const_iterator& it, Ship& ship) {
                tk::core::deserialize(it, ship.position, ship.velocity, ship.rotation, ship.input);
            }
        };

        template <>
        struct convert<ShipInput> {
            void serialize(Blob& blob, const ShipInput& input) {
                uint8_t bitfield = (input.thrust ? 1 : 0) | (input.left ? 2 : 0) | (input.right ? 4 : 0) | (input.shoot ? 8 : 0) | (input.mode ? 16 : 0);
                tk::core::serialize(blob, bitfield, input.target_rotation);
            }

            void deserialize(Blob::const_iterator& it, ShipInput& input) {
                uint8_t bitfield;
                float target_rotation;
                tk::core::deserialize(it, bitfield, target_rotation);
                input.thrust = (bitfield & 1) > 0;
                input.left = (bitfield & 2) > 0;
                input.right = (bitfield & 4) > 0;
                input.shoot = (bitfield & 8) > 0;
                input.mode = (bitfield & 16) > 0;
                input.target_rotation = target_rotation;
            }
        };
    }
}
