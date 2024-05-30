// All of the Packet objects inherit from this class
#pragma once

#include <memory>
#include <linux/if_ether.h>

class Packet{
    public:
        Packet();
        Packet(char *buf);
        void Get_Ethernet_Frame(char *buf);
        char source_mac[6];
        char dest_mac[6];
        unsigned short eth_proto;
    private:
};

enum PacketType {
    ARP_PACKET,
    IPV4_PACKET,
    IPV6_PACKET,
    NotImplemented
};

enum EthernetProtocol {
    ARP = 0x0806,
    IPv4 = 0x0800,
    IPv6 = 0x86DD
};
