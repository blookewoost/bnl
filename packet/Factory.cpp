#include "Packet.h"

enum PacketType {
    IPv4,
    IPv6, 
};

std::unique_ptr<Packet> create_packet(PacketType type, char* buf) {

}

PacketType identify_packet(char* buf) {
    
}