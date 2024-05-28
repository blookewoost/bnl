#include "../packet/Packet.h"
#include <iomanip>
#include <iostream>

struct MacPair {
    std::string source_mac;
    std::string dest_mac;
};

MacPair stringify_mac(Packet packet);