#include "Packet.h"
#include <linux/in6.h>
#include <arpa/inet.h>
#include <string>

class IPv6 : public Packet{
    public:
        IPv6();
        IPv6(char *buf);
        std::string source_addr;
        std::string dest_addr;
    private:
        void Extract_IPv6_Header(char *buf);
};