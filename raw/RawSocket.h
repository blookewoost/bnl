#include <vector>
#include <sys/socket.h>

class RawSocket{
    public:
        RawSocket();
        RawSocket(const char* interface);
        std::vector<char> read(std::size_t buffer_size);
    private:
        int sock;
        int s_addr_len;
        struct sockaddr saddr;
};