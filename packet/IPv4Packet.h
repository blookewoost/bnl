#include "Packet.h"

class IPv4Packet : public Packet {
    public:
        IPv4Packet(char *buf);
        char * source_ip;
        char * dest_ip;
        unsigned int ip_protocol;
    private:
        void Extract_IP_Header(char *buf);
        
};
