#include "Packet.h"

class IPv4 : public Packet {
    public:
        IPv4(char *buf);
        char * source_ip;
        char * dest_ip;
        unsigned int ip_protocol;
    private:
        void Extract_IP_Header(char *buf);
        
};
