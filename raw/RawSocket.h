#include <vector>
class RawSocket{
    public:
        RawSocket();
        RawSocket(const char* interface);
        int sock;
        int s_addr_len;
        std::vector<char> read(std::size_t buffer_size);
        
};