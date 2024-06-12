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


// Send a UDP message
bool send_udp_message(std::vector<char> payload, std::string ip, int port) {
    UDPSender s = UDPSender(ip, port);
    if (s.send_bytes(payload)) {
        return true;
    }

    return false;
}

// Read packets on the wire until we find the test UDP Packet.
UDPPacket snoop_with_rawsocket(std::string adapter, int target_port) {

    try
    {
        RawSocket rs = RawSocket(adapter.c_str());
        std::vector<char> buf;

        bool test_packet_found = false;

        while(!test_packet_found) {
            buf = rs.read(1024);
            struct ethhdr *eth = (struct ethhdr*) buf.data();
            switch (htons(eth->h_proto))
            {
                case EthernetProtocol::IPv4: {
                    struct iphdr *ip = (struct iphdr*) (buf.data() + sizeof(struct ethhdr));
                    switch (ip->protocol)
                    { 
                        case IPv4Protocol::UDP: {
                            UDPPacket u = UDPPacket(buf.data());
                            if (int(u.dest_port) == target_port) {
                                test_packet_found = true;
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
                printf("Skipping unrelated packet...\n");
                break;
            }
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}


int main() {

    // Declare constants... These should probably be arguments
    std::string adapter = "lo";
    std::string message = "Hello, raw socket!";
    std::string ip = "127.0.0.1";
    int target_port = 9000;

    // Declare a buffer with our message inside.
    std::vector<char> buffer(message.begin(), message.end());

    // Create a future, running the snoop function asynchronously.
    std::future<UDPPacket> payload = std::async(std::launch::async, snoop_with_rawsocket, adapter, target_port);
    
    // Wait
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Create a thread for our udp send operation and allow it to finish.
    std::thread sender(send_udp_message, buffer, ip, target_port);
    sender.join();

    // Collect our UDP packet from the future we created earlier.
    UDPPacket received = payload.get();

    // Check the contents of what we received.
    if (sizeof(received.payload) > 0) {
        std::string received_message(received.payload.begin(), received.payload.end());
        if (received_message == message) {
            printf("Test passed! The messages match!\n");
            return 0;
        } else {
            printf("Something is wrong, the messages are not equivalent!\n");
        }
    } else {
        printf("Received an empty payload!\n");
    }
}
