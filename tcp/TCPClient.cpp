#include "TCPClient.h"

TCPClient::TCPClient(std::string& ip, int port) {

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock<0) {
        printf("Socket creation failed with error: %d", errno);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &saddr.sin_addr) <= 0) {
        printf("%d is an invalid IP address.", ip);
    }

    s_addr_len = sizeof(saddr);
};

bool TCPClient::connectToListener() {
    if (connect(sock, (struct sockaddr*)&saddr, s_addr_len) < 0) {
        printf("An error occured while trying to connect to TCP Listener!");
        return false;
    } else {
        return true;
    }

}

