// All of the Packet types inherit from this class, 
// since all of the packets will have an Ethernet Frame.

#ifndef PACKET_H
#define PACKET_H

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

#endif
