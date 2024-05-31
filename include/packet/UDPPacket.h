#include "IPv4Packet.h"
#include <netinet/udp.h>

class UDPPacket: public IPv4Packet {
    public:
        UDPPacket(char *buf);
        void Extract_UDP_Header(char *buf);
        uint16_t source_port;
        uint16_t dest_port;
        uint16_t length;
        uint16_t checksum;

};