#include "../RawSocket.h"
#include "../../packet/IPv4.h"
#include "../../udp/UDPReceiver.h"
#include "../../udp/UDPSender.h"
#include "../../packet/Packet.h"
#include "../../utils/lib.h"

#include <vector>
#include <cstdio>
#include <thread>
#include <chrono>
#include <linux/if_ether.h>


// Let's send a UDP packet and snoop on it with our RawSocket
void send_udp() {

    std::string ip = "127.0.0.1";
    UDPSender sender = UDPSender(ip, 9000);

    std::string message = "Hello from UDP sender!";
    std::vector<char> buffer;
    buffer.assign(message.begin(), message.end());

    if (sender.send_bytes(buffer)) {
        
    }
}

void receive_udp() {

    UDPReceiver receiver = UDPReceiver(9000);
    ssize_t buffersize = 1024;
    std::vector<char> buffer = receiver.read(buffersize);
    std::string message(buffer.begin(), buffer.end());
    printf("Received message!: %s", message.c_str());
}

void snoop_with_rs() {
    RawSocket rs = RawSocket("lo");
    std::vector<char> buf = rs.read(1024);
    struct ethhdr *eth = (struct ethhdr*) buf.data();

    switch (eth->h_proto)
    {
    case EthernetProtocol::IPv4:
        IPv4 ipv4_packet = IPv4(buf.data());
        break;
    default:
        printf("Unexpected packet encounter!");
        break;
    }
}

int main() {


    // Declare threads.
    std::thread rs_thread(snoop_with_rs);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread receiver_thread(receive_udp);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread sender_thread(send_udp);
    
    rs_thread.join();
    receiver_thread.join();
    sender_thread.join();

}
