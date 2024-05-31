#include "IPv4Packet.h"
#include <netinet/udp.h>

class UDPPacket: public IPv4Packet {
    public:
        UDPPacket(char *buf);
        void Extract_UDP_Header(char *buf);
        int source_port;
        int dest_port;
        int length;
        int checksum;

};