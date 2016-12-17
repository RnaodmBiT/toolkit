#pragma once
#include <core.hpp>
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

struct Global;

struct ShipInput {
    bool thrust, left, right;

    ShipInput() :
        thrust(false),
        left(false),
        right(false) { }
};

class Ship {
    Vec2f position, velocity;
    float rotation, drag, mass;
    ShipInput input;

    Shape shape;
    Shader* shader;
    friend tk::core::convert<Ship>;
public:
    Ship(Global& global, const Vec2f& position, float rotation);

    void setInput(const ShipInput& input);

    void update(float dt);
    void render(const Mat4f& projection);

    Mat4f getTransform() const;
    Vec2f getDirection() const;

    void thrust(float strength, float dt);
    void rotate(float speed, float dt);
};

namespace tk {
    namespace core {
        template <>
        struct convert<Ship> {
            void serialize(Blob& blob, const Ship& ship) {
                tk::core::serialize(blob, ship.position, ship.velocity, ship.rotation, ship.drag, ship.mass, ship.input);
            }

            void deserialize(Blob::const_iterator& it, Ship& ship) {
                tk::core::deserialize(it, ship.position, ship.velocity, ship.rotation, ship.drag, ship.mass, ship.input);
            }
        };

        template <>
        struct convert<ShipInput> {
            void serialize(Blob& blob, const ShipInput& input) {
                tk::core::serialize(blob, input.thrust, input.left, input.right);
            }

            void deserialize(Blob::const_iterator& it, ShipInput& input) {
                tk::core::deserialize(it, input.thrust, input.left, input.right);
            }
        };
    }
}