#include "Packet.h"
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <arpa/inet.h>

class IPv4Packet : public Packet {
    public:
        IPv4Packet();
        IPv4Packet(char *buf);
        void Extract_IP_Header(char *buf);
        char * source_ip;
        char * dest_ip;
        unsigned int ip_protocol;
    private:
};
