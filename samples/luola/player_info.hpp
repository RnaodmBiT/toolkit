#pragma once
#include <string>
#include <core.hpp>

struct PlayerInfo {
    std::string name;
    int ship;
};

namespace tk {
    namespace core {
        template <>
        struct tk::core::convert<PlayerInfo> {
            void serialize(Blob& blob, const PlayerInfo& info) {
                tk::core::serialize(blob, info.name, info.ship);
            }

            void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
                tk::core::deserialize(it, info.name, info.ship);
            }
        };
    }
}
