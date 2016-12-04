#include "player_info.hpp"
#include <player_table.hpp>


namespace tk {
    namespace core {
        void serialize(Blob& blob, const PlayerInfo& info) {
            serialize(blob, info.name);
        }

        void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
            deserialize(it, info.name);
        }

    }
}

