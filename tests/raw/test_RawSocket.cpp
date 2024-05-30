#include "../../include/raw/RawSocket.h"
#include "../../include/packet/IPv4Packet.h"
#include "../../include/udp/UDPReceiver.h"
#include "../../include/udp/UDPSender.h"
#include "../../include/packet/Packet.h"
#include "../../include/utils/lib.h"

#include <vector>
#include <cstdio>
#include <thread>
#include <chrono>
#include <linux/if_ether.h>

// Our RawSocket should be able to see any network traffic on the specified adapter.
// In order to test it, let's send a UDP packet over the loopback adapter and snoop on it with the RawSocket.
// 
// We can intercept the packet on the 'wire' and deconstruct it with our Packet tools, then check the payload contents.
// If the payload we intercept with the RawSocket is the same as what we sent over UDP, then the raw socket performed as expected!




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

    switch (htons(eth->h_proto))
    {
    case EthernetProtocol::IPv4: {
        IPv4Packet ipv4_packet = IPv4Packet(buf.data());
        break;
    }
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
