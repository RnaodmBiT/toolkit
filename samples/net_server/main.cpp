#include <core.hpp>
#include <net.hpp>

using namespace tk::core;
using namespace tk::net;

struct PlayerInfo {
    std::string name;
};

int main(int argc, char** argv) {

    tk::net::initialize();

    Server<PlayerInfo> server;
    server.start(25140);
    tk_info("Server started");

    while (1) {
        server.pollEvents();
    }

    return 0;
}

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