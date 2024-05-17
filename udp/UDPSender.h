#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class UDPSender{
    public:
        UDPSender::UDPSender();
        UDPSender::UDPSender(std::string& ip, int port);
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
};  