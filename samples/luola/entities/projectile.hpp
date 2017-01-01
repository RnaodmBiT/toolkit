#pragma once
#include <core.hpp>
#include <graphics.hpp>
#include "projectile_types.hpp"

using namespace tk::core;
using namespace tk::graphics;

struct Global;

class Projectile {
    Vec2f position, velocity;
    float drag, mass, rotation;
    int type;

    Shape shape;
    Shader* shader;
    friend tk::core::convert<Projectile>;
public:
    Projectile(Global& global, const Vec2f& position, const Vec2f& velocity, float rotation, int type);

    void update(float dt);
    void draw(const Mat4f& projection);
    Vec2f getPosition();
    Vec2f getVelocity();

    int getType();

    Mat4f getTransform() const;
};

namespace tk {
    namespace core {
        template <>
        struct convert<Projectile> {
            void serialize(Blob& blob, const Projectile& p) {
                tk::core::serialize(blob, p.position, p.rotation, p.velocity, p.type);
            }

            void deserialize(Blob::const_iterator& it, Projectile& p) {
                tk::core::deserialize(it, p.position, p.rotation, p.velocity, p.type);
            }
        };
    }
}