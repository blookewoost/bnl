#include "../UDPReceiver.h"
#include <iostream>
#include <iomanip>

int main() {
    UDPReceiver receiver = UDPReceiver(5000);
    std::vector<char> receivedbytes = receiver.read(1024);

    std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)receivedbytes[0];
}