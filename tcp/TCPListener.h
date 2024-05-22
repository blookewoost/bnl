#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

class TCPListener{
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
    public:
        TCPListener(int port);
        bool start_listening(int timeout);
        int accept_connection();
};