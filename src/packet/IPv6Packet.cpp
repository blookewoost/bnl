#include "../../include/packet/IPv6Packet.h"
#include <linux/ipv6.h>
#include <linux/if_ether.h>
#include <string>
#include <arpa/inet.h>

IPv6Packet::IPv6Packet(char *buf) {

    IPv6Packet::Get_Ethernet_Frame(buf);
    IPv6Packet::Extract_IPv6_Header(buf);
}

void IPv6Packet::Extract_IPv6_Header(char *buf) {

    struct ipv6hdr *ipv6 = (struct ipv6hdr*) (buf + sizeof(struct ethhdr));

    struct in6_addr source_addr = ipv6->saddr;
    struct in6_addr dest_addr = ipv6->daddr;

    char saddr[INET6_ADDRSTRLEN];
    char daddr[INET6_ADDRSTRLEN];

    // Implicit cast to std::string
    IPv6Packet::source_addr = inet_ntop(AF_INET6, &source_addr, saddr, sizeof(saddr));
    IPv6Packet::dest_addr = inet_ntop(AF_INET6, &dest_addr, daddr, sizeof(daddr));

}