#pragma once
#include <unordered_map>
#include "../entities/projectile.hpp"

struct Global;

class ProjectileManager {
    Global& global;
    std::unordered_map<int, Projectile> projectiles;
    int id;

    friend tk::core::convert<ProjectileManager>;
public:

    ProjectileManager(Global& global);

    int spawn(const Vec2f& position, const Vec2f& shipVelocity, float rotation);
    Projectile* spawnWithID(int id, const Vec2f& position, const Vec2f& shipVelocity, float rotation);

    Projectile* get(int id);

    void update(float dt);
    void draw(const Mat4f& projection);
};

namespace tk {
    namespace core {
        template <>
        struct convert<ProjectileManager> {
            void serialize(Blob& blob, const ProjectileManager& projectiles) {
                tk::core::serialize(blob, (int)projectiles.projectiles.size());
                for (auto& pair : projectiles.projectiles) {
                    tk::core::serialize(blob, pair.first, pair.second);
                }
            }

            void deserialize(Blob::const_iterator& it, ProjectileManager& projectiles) {
                int count, id;
                tk::core::deserialize(it, count);
                for (int i = 0; i < count; ++i) {
                    tk::core::deserialize(it, id);
                    Projectile* projectile = projectiles.get(id);
                    if (projectile == nullptr) {
                        projectile = projectiles.spawnWithID(id, { 0, 0 }, { 0, 0 }, 0);
                    }
                    tk::core::deserialize(it, *projectile);
                }
            }
        };
    }
}
