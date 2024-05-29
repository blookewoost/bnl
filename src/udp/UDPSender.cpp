#include "../../include/udp/UDPSender.h"

UDPSender::UDPSender(std::string& ip, int port) {

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0) {
        printf("Socket creation failed with error: %d", errno);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &saddr.sin_addr) < 0) {
        printf("An invalid IP address was provided! inet_pton failed.");
    }

    s_addr_len = sizeof(saddr);
}

UDPSender::~UDPSender() {
    close(sock);
}

bool UDPSender::send_bytes(std::vector<char> buffer) {
    ssize_t sent_bytes = sendto(sock, buffer.data(), buffer.size(), 0, (struct sockaddr*)&saddr, s_addr_len);
    if(buffer.size() == sent_bytes) {
        return true;
    } else {
        printf("Something unexpected happened, and the sendto() operation failed!");
        return false;
    }
}