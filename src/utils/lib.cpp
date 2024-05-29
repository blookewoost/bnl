#include "../../include/utils/lib.h"
#include <sstream>

MacPair stringify_mac(Packet packet) {

    std::stringstream sstream;
    for (int i=1;i<=sizeof(packet.source_mac);i++) {
        sstream << std::setfill('0') << std::setw(2) << std::hex << (int)packet.source_mac[i-1];
        if (i<(sizeof(packet.source_mac))) {
            sstream << ":";
        }
    }

    std::string source_mac = sstream.str();

    //sstream.clear(); This clearly doesn't do what I expected
    sstream.str(""); // Reset the buffer

    for (int i=1;i<=sizeof(packet.dest_mac); i++) {
        sstream << std::setfill('0') << std::setw(2) << std::hex << (int)packet.dest_mac[i-1];
        if (i<(sizeof(packet.dest_mac))) {
            sstream << ":";
        }
    }

    std::string dest_mac = sstream.str();

    return MacPair{source_mac, dest_mac};
}
