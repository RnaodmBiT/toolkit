#include <core.hpp>
#include <net.hpp>
#include <string>

using namespace tk::core;
using namespace tk::net;

struct PlayerInfo {
    std::string name;
};

int main(int argc, char** argv) {

    std::string name = "Client";
    if (argc == 2) {
        name = argv[1];
    }

    tk::net::initialize();

    Client<PlayerInfo> client;
    client.connect("localhost", 25140, { name });

    while (1) {
        client.pollEvents();
    }

    return 0;
}

void serialize(Blob& blob, const PlayerInfo& info) {
    serialize(blob, info.name);
}

void deserialize(Blob::const_iterator& it, PlayerInfo& info) {
    deserialize(it, info.name);
}