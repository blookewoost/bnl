#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

class TCPClient{
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
    public:
        TCPClient(std::string& ip, int port);
        bool connect_to_listener();
        bool send_bytes(std::vector<char> buffer);
        std::vector<char> receive_bytes(ssize_t buffersize);
};
