#include "../../include/raw/RawSocket.h"

// Create a raw socket and bind it to the specified interface.
RawSocket::RawSocket(const char* interface) {

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock<0) {
        printf("Socket creation failed with error %d\n", errno);
        //figure out how to return an error object
    }

    s_addr_len = sizeof(saddr);

    // Specify the adapter we want to listen on
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, sizeof(ifr.ifr_name) - 1);

    // Bind socket to a specific network interface
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        printf("Binding to interface: %s failed with error %d\n", interface, errno);
    }

}

// Read the specified number of bytes from the wire.
std::vector<char> RawSocket::read(std::size_t buffer_size) {

    std::vector<char> buf(buffer_size);
    
    int read = recvfrom(sock, buf.data(), buffer_size, 0, &saddr, (socklen_t *)&s_addr_len);

    if (read<0) {
        printf("Call to recvfrom failed with error %d\n", errno);
    } else {
        return buf;
    }
}

RawSocket::~RawSocket() {
    close(sock);
}