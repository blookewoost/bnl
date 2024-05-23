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

bool TCPListener::start_listening(int timeout) {
    if (listen(sock, SOMAXCONN) < 0) {
        printf("Failed to start listening!");
        return false;
    }
    return true;
}

int TCPListener::accept_connection() {
    struct sockaddr_in cli_addr;
    int cli_addr_len = sizeof(cli_addr);

    int cli_sock = accept(sock, (sockaddr *)&cli_addr, (socklen_t*)&cli_addr_len);
    if (cli_sock < 0) {
        printf("accept() failed to return a valid client socket!");
        return -1;
    } else {
        //return the client socket
        return cli_sock;
    }
}

std::vector<char> TCPListener::receive_bytes(int cli_sock, ssize_t buffersize) {

    std::vector<char> buffer(buffersize);

    ssize_t receivedBytes = recv(cli_sock, buffer.data(), buffer.size(), 0);
    if (receivedBytes < 0) {
        printf("An error occurred during the recv() call!");
    }

    return buffer;
}

bool TCPListener::send_bytes(int cli_sock, std::vector<char> buffer) {

    ssize_t sent_bytes = send(cli_sock, buffer.data(), buffer.size(), 0);

    if (sent_bytes == buffer.size()) {
        return true;
    } 

    printf("Something went wrong in the call to send()!");
}

