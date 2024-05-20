#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

class TCPClient{
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
    public:
        TCPClient(std::string& ip, int port);
        bool connectToListener();
};
