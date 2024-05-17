#include "UDPSender.h"
#include <string>
#include <sys/socket.h>

UDPSender::UDPSender() {

}

UDPSender::UDPSender(std::string& ip, int port) {

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0) {
        printf("Socket creation failed with error: %d", errno);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = port;
    if (inet_pton(AF_INET, ip.c_str(), &saddr.sin_addr) < 0) {
        printf("An invalid IP address was provided! inet_pton failed.");
    }

    
}