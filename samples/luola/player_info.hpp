#pragma once
#include <string>
#include <core.hpp>

enum Team {
    Blue,
    Red,
};

struct PlayerInfo {
    std::string name;
    int ship;
    Team team;
};

namespace tk {
    namespace core {
        template <>
        struct tk::core::convert<PlayerInfo> {
            void serialize(Blob& blob, const PlayerInfo& info) {
                tk::core::serialize(blob, info.name, info.ship, (uint8_t)info.team);
            }

            void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
                uint8_t team;
                tk::core::deserialize(it, info.name, info.ship, team);
                info.team = (Team)team;
            }
        };
    }
}
