#pragma once

#include <blob.hpp>
#include <string>
#include <player_table.hpp>

struct PlayerInfo {
    std::string name;

    PlayerInfo(std::string name = std::string()) : name(name) { }
};

namespace tk {
    namespace core {
        template <>
        struct convert<PlayerInfo> {
            void serialize(Blob& blob, const PlayerInfo& info) {
                tk::core::serialize(blob, info.name);
            }

            void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
                tk::core::deserialize(it, info.name);
            }
        };
    }
}
