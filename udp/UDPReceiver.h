#include <arpa/inet.h>
#include <cstdio>
#include <vector>

class UDPReceiver{
    public:
        UDPReceiver(int port);
        std::vector<char> read(std::size_t buffersize);
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
};