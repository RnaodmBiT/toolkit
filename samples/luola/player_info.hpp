#pragma once

#include <core.hpp>
#include <string>

struct PlayerInfo {
    std::string name;

    PlayerInfo(std::string name = std::string()) : name(name) { }
};

namespace tk {
    namespace core {
        static void serialize(Blob& blob, const PlayerInfo& info) {
            serialize(blob, info.name);
        }

        static void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
            deserialize(it, info.name);
        }
    }
}