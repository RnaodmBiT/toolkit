#include "player_info.hpp"
#include <player_table.hpp>


namespace tk {
    namespace core {
        template <>
        void serialize(Blob& blob, const PlayerInfo& info) {
            serialize(blob, info.name);
        }

        template <>
        void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
            deserialize(it, info.name);
        }

        template <>
        void serialize(Blob& blob, const net::PlayerTable<PlayerInfo>& table) {
            serialize(blob, (int)table.playerList.size());
            for (int i = 0; i < table.playerList.size(); ++i) {
                serialize(blob, table.playerList[i].id, table.playerList[i].info);
            }
        }

        template <>
        void deserialize(Blob::const_iterator& it, net::PlayerTable<PlayerInfo>& table) {
            int size;
            deserialize(it, size);
            table.playerList.clear();
            table.playerList.resize(size);
            for (int i = 0; i < size; ++i) {
                table.playerList[i].handle = nullptr;
                deserialize(it, table.playerList[i].id, table.playerList[i].info);
            }
        }

    }
}

