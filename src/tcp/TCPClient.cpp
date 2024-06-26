#include "../../include/tcp/TCPClient.h"

TCPClient::TCPClient(std::string& ip, int port) {

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock<0) {
        throw std::runtime_error("TCPClient socket creation failed!");
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &saddr.sin_addr) <= 0) {
        throw std::runtime_error("TCPClient cannot use invalid IP address");
    }

    s_addr_len = sizeof(saddr);
};

TCPClient::~TCPClient() {
    close(sock);
}

bool TCPClient::connect_to_listener() {
    if (connect(sock, (struct sockaddr*)&saddr, s_addr_len) < 0) {
        return false;
    } else {
        return true;
    }
}

bool TCPClient::send_bytes(std::vector<char> buffer) {
    ssize_t sent_bytes = send(sock, buffer.data(), buffer.size(), 0);
    if (sent_bytes == buffer.size()) {
        return true;
    } else {
        return false;
    }
}

std::vector<char> TCPClient::receive_bytes(ssize_t buffersize) {
    std::vector<char> buffer(buffersize);
    ssize_t received_bytes = recv(sock, buffer.data(), buffer.size(), 0);
    
    if(received_bytes < 0) {
        throw std::runtime_error("Something unexpected occurred when attempting to receive bytes"); // is this even possible?
    } else {
        return buffer;
    }
}

