#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdexcept>
#include <vector>

class TCPListener{
    private:
        int sock;
        struct sockaddr_in saddr;
        int s_addr_len;
    public:
        TCPListener(int port);
        ~TCPListener();
        bool start_listening();
        int accept_connection();
        bool send_bytes(int cli_sock, std::vector<char> buffer);
        std::vector<char> receive_bytes(int cli_sock, ssize_t buffersize);
};