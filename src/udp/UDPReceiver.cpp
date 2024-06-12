#include "../../include/udp/UDPReceiver.h"

UDPReceiver::UDPReceiver(int port) {

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0) {
        throw std::runtime_error("UDPReceiver socket creation failed!");
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);

    s_addr_len = sizeof(saddr);

    if (bind(sock, (struct sockaddr*)&saddr, s_addr_len) <0) {
        throw std::runtime_error("UDPReceiver failed to bind to the socket. Check the port number");
    }
}

UDPReceiver::~UDPReceiver(){
    close(sock);
}

std::vector<char> UDPReceiver::read(std::size_t buffersize) {
    
    std::vector<char> buffer(buffersize);
    std::size_t bytesread = recvfrom(sock, buffer.data(), buffersize, 0, (struct sockaddr*)&saddr, (socklen_t*)&s_addr_len);

    if (bytesread<0) {
        throw std::runtime_error("UDPReceiver: Something unexpected occurred when attempting to receive bytes"); // is this even possible?
    } else {
        return buffer;
    }
}