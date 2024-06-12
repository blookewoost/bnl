#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdexcept>
#include <string.h>
#include <cstddef>

class RawSocket{
    public:
        RawSocket(const char* interface);
        ~RawSocket();
        std::vector<char> read(std::size_t buffer_size);
    private:
        int sock;
        int s_addr_len;
        struct sockaddr saddr;
};