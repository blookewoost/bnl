#include "RawSocket.h"
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// Figure out if we can remove this empty constructor.
RawSocket::RawSocket() {

}

// Create a raw socket and bind it to the specified interface.
RawSocket::RawSocket(const char* interface) {

    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock<0) {
        printf("Socket creation failed with error %d", errno);
        //figure out how to return an error object
    }

    unsigned char buf[1024];
    struct sockaddr saddr;
    int s_addr_len = sizeof(saddr);

    // Specify the adapter we want to listen on
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, interface, sizeof(ifr.ifr_name) - 1);

    // Bind socket to a specific network interface
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        printf("Binding to interface: %s failed with error %d", interface, errno);
    }

}