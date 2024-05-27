#include "Packet.h"

std::unique_ptr<Packet> create_packet(PacketType type, char* buf) {

}

// Determine what kind of packet we're dealing with.
PacketType identify_packet(char* buf) {

    struct ethhdr *eth = (struct ethhdr *)(buf);
    switch (eth->h_proto)
    {
    case EthernetProtocol::IPv4:
        return PacketType::IPv4;
        break;
    case EthernetProtocol::IPv6:
        return PacketType::IPv6;
        break;
    case EthernetProtocol::ARP:
        return PacketType::ARP;
        break;
    default:
        return PacketType::NotImplemented;
        break;
    }
}