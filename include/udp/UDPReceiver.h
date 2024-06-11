#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <vector>

class UDPReceiver{
    public:
        UDPReceiver(int port);
        ~UDPReceiver();
        std::vector<char> read(std::size_t buffersize);
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
};