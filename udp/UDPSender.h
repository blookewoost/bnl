#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <vector>
#include <arpa/inet.h>

class UDPSender{
    public:
        UDPSender(std::string& ip, int port);
        bool send_bytes(std::vector<char> buffer);
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
};  