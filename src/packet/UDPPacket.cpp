#include "../../include/packet/UDPPacket.h"

UDPPacket::UDPPacket(char *buf) {
    Get_Ethernet_Frame(buf);
    Extract_IP_Header(buf);
}

void UDPPacket::Extract_UDP_Header(char *buf) {
    struct udphdr *udp = (struct udphdr*) (buf + (sizeof(struct ethhdr) + sizeof(struct iphdr)));
    source_port = htons(udp->source);
    dest_port = htons(udp->dest);
    length = htons(udp->len);
    checksum = htons(udp->check);
}