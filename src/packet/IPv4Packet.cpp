#include "../../include/packet/IPv4Packet.h"

IPv4Packet::IPv4Packet() {

}

IPv4Packet::IPv4Packet(char *buf) {
    IPv4Packet::Get_Ethernet_Frame(buf);
    IPv4Packet::Extract_IP_Header(buf);
}


void IPv4Packet::Extract_IP_Header(char *buf) {

    struct iphdr *ip = (struct iphdr*) (buf + sizeof(struct ethhdr));

    struct sockaddr_in source;
    source.sin_addr.s_addr = ip->saddr;
    struct sockaddr_in dest;
    dest.sin_addr.s_addr = ip->saddr;

    IPv4Packet::source_ip = inet_ntoa(source.sin_addr);
    IPv4Packet::dest_ip = inet_ntoa(dest.sin_addr);
    IPv4Packet::ip_protocol = (unsigned int)ip->protocol;

}

