#include "../../include/raw/RawSocket.h"
#include "../../include/packet/UDPPacket.h"
#include "../../include/udp/UDPReceiver.h"
#include "../../include/udp/UDPSender.h"
#include "../../include/packet/Packet.h"
#include "../../include/utils/lib.h"

#include <vector>
#include <cstdio>
#include <thread>
#include <chrono>
#include <linux/if_ether.h>
#include <future>

// Our RawSocket should be able to see any network traffic on the specified adapter.
// In order to test it, let's send a UDP packet over the loopback adapter and snoop on it with the RawSocket.
// 
// We can intercept the packet on the 'wire' and deconstruct it with our Packet tools, then check the payload contents.
// If the payload we intercept with the RawSocket is the same as what we sent over UDP, then the raw socket performed as expected!


bool send_udp_message(std::vector<char> payload, std::string ip, int port) {
    UDPSender s = UDPSender(ip, port);
    if (s.send_bytes(payload)) {
        return true;
    }

    return false;
}


UDPPacket snoop_with_rawsocket(std::string adapter) {

    RawSocket rs = RawSocket(adapter.c_str());
    std::vector<char> buf;


    bool test_packet_found = false;
    while(!test_packet_found) {
        buf = rs.read(1024);
        struct ethhdr *eth = (struct ethhdr*) buf.data();
        printf("eth proto: %d", htons(eth->h_proto));
        switch (htons(eth->h_proto))
        {
            case EthernetProtocol::IPv4: {
                struct iphdr *ip = (struct iphdr*) (buf.data() + sizeof(struct ethhdr));
                switch (ip->protocol)
                { 
                    case IPv4Protocol::UDP: {
                        UDPPacket u = UDPPacket(buf.data());
                        printf("%i, %i", u.source_port, u.dest_port);
                        printf("%i", int(u.dest_port));
                        if (int(u.dest_port) == 9000) {
                            printf("We found our test packet! hooray!\n");
                            
                            test_packet_found = true;
                            printf("Returning buf\n");
                            return u;
                        }
                        break;
                    }
                    case IPv4Protocol::TCP:
                        break;
                    default:
                        break;
                }
            break;
        }
        default:
            printf("Unexpected packet encounter!");
            break;
        }
    }
}

// Let's send a UDP packet and snoop on it with our RawSocket
void send_udp() {

    std::string ip = "127.0.0.1";
    UDPSender sender = UDPSender(ip, 9111);

    std::string message = "Hello from UDP sender!";
    std::vector<char> buffer;
    buffer.assign(message.begin(), message.end());

    if (sender.send_bytes(buffer)) {
        
    }
}


int main() {

    // Declare threads.
    std::string adapter = "lo";
    std::string message = "Hello, raw socket!";

    std::vector<char> buffer;
    buffer.assign(message.begin(), message.end());

    std::future<UDPPacket> payload = std::async(std::launch::async, snoop_with_rawsocket, adapter);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread sender(send_udp_message, buffer, "127.0.0.1", 9000);

    
    sender.join();
    UDPPacket received = payload.get();
    if (sizeof(received.payload) > 0) {
        printf("We found the test packet!");
    }

    std::string received_message(received.payload.begin(), received.payload.end());
    if(received_message.size() == message.size()) {
        printf("Messages are the same size!\n");
    } else {
        printf("Received size %lu, Sent size %lu", received_message.size(), message.size());
    }

    if (received_message == message) {
        printf("We passed the test! The messages match!\n");
        return 0;
    }
    else{
        printf("Whats wrong: %s %s", message.c_str(), received_message.c_str());
        return -1;
    }

}
