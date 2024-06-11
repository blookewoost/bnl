#include "../../include/udp/UDPReceiver.h"
#include "../../include/udp/UDPSender.h"
#include <thread>
#include <chrono>

void sender() {
    std::string ip = "127.0.0.1";
    UDPSender sender = UDPSender(ip, 9000);
    std::string message = "Hello from the sender!";
    std::vector<char> buffer;

    buffer.assign(message.begin(), message.end());
    sender.send_bytes(buffer);
}


void receiver() {
    UDPReceiver receiver = UDPReceiver(9000);
    ssize_t buffersize = 1024;
    std::vector<char> buffer = receiver.read(buffersize);

    std::string message(buffer.begin(), buffer.end());
    printf("Received a message from the sender:\n %s", message.c_str());
}


int main() {
    std::thread receiver_thread(receiver);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread sender_thread(sender);

    receiver_thread.join();
    sender_thread.join();
}
