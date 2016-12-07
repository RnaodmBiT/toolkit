#pragma once
#include <core.hpp>
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

struct PlayerInput {
    enum Keys { None = 0, Thrust = 1, Left = 2, Right = 4, Mouse = 8 } input;
    float angle;

    PlayerInput() : input(None), angle(0) { }

    void toggleMouse() {
        if (input & Mouse) {
            input = (Keys)(input & ~Mouse);
        } else {
            input = (Keys)(input | Mouse);
        }
    }

    void clear() {
        input = input & Mouse ? Mouse : None;
    }

    void set(Keys key) {
        input = (Keys)(input | key);
    }
};

class Ship {
    std::unique_ptr<ShapeNode> shape;
    PlayerInput input;

    Vec2f position, velocity;
    float angle;
    int id;

    void updateTransform();

public:
    Ship();
    Ship(int player, Vec2f position, Vec4f color, ShapeNode* shape);
    ~Ship();

    Ship(Ship&& move) {
        *this = std::move(move);
    }

    void operator=(Ship&& move) {
        std::swap(shape, move.shape);
        std::swap(position, move.position);
        std::swap(velocity, move.velocity);
        std::swap(angle, move.angle);
        std::swap(id, move.id);
    }

    void update(float dt);
    void updateInput(float dt);
    void setInput(const PlayerInput& input);

    Vec2f getDirection() const;
    Vec2f getPosition() const;
    float getAngle() const;

    void setPosition(const Vec2f&);
    void setAngle(float angle);

    ShapeNode* getNode() const;
    int getID() const;

    void applyThrust(float thrust, float dt);
    void rotate(float speed, float dt);
};

namespace tk {
    namespace core {
        template <>
        struct convert<PlayerInput> {
            void serialize(Blob& blob, PlayerInput const& input) {
                tk::core::serialize(blob, (uint8_t)input.input, input.angle);
            }

            void deserialize(Blob::const_iterator& it, PlayerInput& input) {
                uint8_t state;
                tk::core::deserialize(it, state, input.angle);
                input.input = (PlayerInput::Keys)state;
            }
        };
    }
}