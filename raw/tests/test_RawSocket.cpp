#include "../RawSocket.h"
#include <vector>
#include <cstdio>

int main() {
    // create raw socket on the loopback adapter.
    RawSocket socket = RawSocket("lo");
    std::vector<char> buf = socket.read(1024);
    printf(buf.data());
}