#include "TCPListener.h"

TCPListener::TCPListener(int port) {

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock<0) {
        printf("An error occured while creating the socket!");
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);

    s_addr_len = sizeof(saddr);

    if (bind(sock, (struct sockaddr*)&saddr, s_addr_len) < 0) {
        printf("Binding the socket to saddr failed!");
    }
};

