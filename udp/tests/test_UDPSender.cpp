#include "../UDPSender.h"
#include <string>

int main() {
    std::string ip = "127.0.0.1";
    UDPSender sender = UDPSender(ip,5000);
    std::vector<char> buffer;
    buffer.push_back(0xFF);
    sender.send_bytes(buffer);
}