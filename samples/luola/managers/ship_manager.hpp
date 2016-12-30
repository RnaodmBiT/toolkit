#pragma once
#include <unordered_map>
#include "../entities/ship.hpp"
#include "player_table.hpp"
#include "../player_info.hpp"

struct Global;

class ShipManager {
    Global& global;
    std::unordered_map<int, Ship> ships;
    int id;
    friend tk::core::convert<ShipManager>;
public:

    typedef std::unordered_map<int, Ship>::iterator iterator;

    ShipManager(Global& global);

    int spawn(int owner, const Vec2f& position, float rotation);
    Ship* spawnWithID(int id, int owner, const Vec2f& position, float rotation);

    Ship* get(int id);

    void update(float dt);
    void draw(const Mat4f& projection);

    iterator begin();
    iterator end();
};

namespace tk {
    namespace core {
        template <>
        struct convert<ShipManager> {
            void serialize(Blob& blob, const ShipManager& ships) {
                tk::core::serialize(blob, (int)ships.ships.size());
                for (auto& pair : ships.ships) {
                    tk::core::serialize(blob, pair.first, pair.second);
                }
            }

            void deserialize(Blob::const_iterator& it, ShipManager& ships) {
                int count, id;
                tk::core::deserialize(it, count);
                for (int i = 0; i < count; ++i) {
                    tk::core::deserialize(it, id);
                    Ship* ship = ships.get(id);
                    if (ship == nullptr) {
                        ship = ships.spawnWithID(id, -1, { 0, 0 }, 0);
                    }
                    tk::core::deserialize(it, *ship);
                }
            }
        };
    }
}
