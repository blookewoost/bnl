#include "../../include/packet/UDPPacket.h"

UDPPacket::UDPPacket(char *buf) {
    Get_Ethernet_Frame(buf);
    Extract_IP_Header(buf);
    Extract_UDP_Header(buf);
    Extract_Payload(buf);
}

void UDPPacket::Extract_UDP_Header(char *buf) {
    struct udphdr *udp = (struct udphdr*) (buf + (sizeof(struct ethhdr) + sizeof(struct iphdr)));
    source_port = ntohs(udp->uh_sport);
    dest_port = ntohs(udp->uh_dport);
    length = ntohs(udp->len);
    checksum = ntohs(udp->check);
}

void UDPPacket::Extract_Payload(char *buf) {
    ssize_t headersize = sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr);
    payload.resize(length-sizeof(struct udphdr));
    std::copy(buf + headersize, buf + headersize + (length-sizeof(struct udphdr)), payload.begin());
}