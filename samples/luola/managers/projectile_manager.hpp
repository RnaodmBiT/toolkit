#pragma once
#include <unordered_map>
#include "../entities/projectile.hpp"
#include "ship_manager.hpp"
#include <unordered_set>

struct Global;

class ProjectileManager {
    Global& global;
    std::unordered_map<int, Projectile> projectiles;
    int id;

    friend tk::core::convert<ProjectileManager>;
public:

    typedef std::unordered_map<int, Projectile>::iterator iterator;
    ProjectileManager(Global& global);
    void checkCollisions(ShipManager* ship_man, float dt);
    int spawn(const Vec2f& position, const Vec2f& shipVelocity, float rotation);
    Projectile* spawnWithID(int id, const Vec2f& position, const Vec2f& shipVelocity, float rotation);

    Projectile* get(int id);

    void removeProjectile(int id);
    void update(float dt);
    void draw(const Mat4f& projection);

    iterator begin();
    iterator end();
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
                std::unordered_set<int> recieved_ids;
                for (int i = 0; i < count; ++i) {
                    tk::core::deserialize(it, id);
                    recieved_ids.emplace(id);
                    Projectile* projectile = projectiles.get(id);
                    if (projectile == nullptr) {
                        projectile = projectiles.spawnWithID(id, { 0, 0 }, { 0, 0 }, 0);
                    }
                    tk::core::deserialize(it, *projectile);
                }
                for (auto& proj : projectiles) {
                    if (recieved_ids.count(proj.first) == 0) {
                        projectiles.removeProjectile(proj.first);
                    }
                }
            }
        };
    }
}
