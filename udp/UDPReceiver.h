#include <arpa/inet.h>
#include <cstdio>

class UDPReceiver{
    public:
        UDPReceiver(int port);
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
};