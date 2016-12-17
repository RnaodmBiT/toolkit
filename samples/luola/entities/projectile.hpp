#pragma once
#include <core.hpp>
#include <graphics.hpp>

using namespace tk::core;
using namespace tk::graphics;

struct Global;

class Projectile {
    Vec2f position, velocity;
    float drag, mass;

    Shape shape;
    Shader* shader;
    friend tk::core::convert<Projectile>;
public:
    Projectile(Global& global, const Vec2f& position, const Vec2f& velocity, float rotation);

    void update(float dt);
    void render(const Mat4f& projection);

    Mat4f getTransform() const;
};

namespace tk {
    namespace core {
        template <>
        struct convert<Projectile> {
            void serialize(Blob& blob, const Projectile& p) {
                tk::core::serialize(blob, p.position, p.velocity);
            }

            void deserialize(Blob::const_iterator& it, Projectile& p) {
                tk::core::deserialize(it, p.position, p.velocity);
            }
        };
    }
}