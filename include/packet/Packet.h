// All of the Packet objects inherit from this class
#pragma once

#include <memory>
#include <linux/if_ether.h>
#include <vector>
#include <algorithm>

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


enum EthernetProtocol {
    ARP = 0x0806,
    IPv4 = 0x0800,
    IPv6 = 0x86DD
};

enum IPv4Protocol {
    UDP = 0x011,
    TCP = 0x06
};
