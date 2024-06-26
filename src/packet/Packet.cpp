#include "../../include/packet/Packet.h"
#include <linux/if_ether.h>
#include <cstring>

Packet::Packet() {
    
}

Packet::Packet(char *buf) {
    Packet::Get_Ethernet_Frame(buf);
}

void Packet::Get_Ethernet_Frame(char *buf){
    struct ethhdr *eth = (struct ethhdr*) buf;
    if (eth) {
        std::memcpy(Packet::source_mac, eth->h_source, sizeof(eth->h_source));
        std::memcpy(Packet::dest_mac, eth->h_dest, sizeof(eth->h_dest));
        Packet::eth_proto = eth->h_proto;
    }
}