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

        void serialize(Blob& blob, const PlayerInfo& info) {
            serialize(blob, info.name);
        }

        void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
            deserialize(it, info.name);
        }

    }
}