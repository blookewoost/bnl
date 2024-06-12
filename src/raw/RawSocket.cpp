#include "../../include/raw/RawSocket.h"

// Create a raw socket and bind it to the specified interface.
RawSocket::RawSocket(const char* interface) {

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock<0) {
        throw std::runtime_error("RawSocket creation failed! (Are you running with sudo?)");
    }

    s_addr_len = sizeof(saddr);

    // Specify the adapter we want to listen on
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, sizeof(ifr.ifr_name) - 1);

    // Bind socket to a specific network interface
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        throw std::runtime_error("Binding RawSocket to the provided interface failed!");
    }

}

// Read the specified number of bytes from the wire.
std::vector<char> RawSocket::read(std::size_t buffer_size) {

    std::vector<char> buf(buffer_size);
    int read = recvfrom(sock, buf.data(), buffer_size, 0, &saddr, (socklen_t *)&s_addr_len);

    if (read<0) {
        throw std::runtime_error("Something unexpected occurred when attempting to receive bytes on RawSocket");
    } else {
        return buf;
    }
}

RawSocket::~RawSocket() {
    close(sock);
}