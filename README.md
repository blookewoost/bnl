## Blooke's Networking Library (BNL)

Networking utilities for common socket operations. Use BNL for any basic TCP/UDP networking code, or to create a RawSocket and explore the network stack with the /packet utilities. 

Example: Sending a UDP Packet

```c++
#include "bnl/include/udp/UDPSender.h" //also includes <string>

int main() {
  
  std::string message = "Hello from UDPSender!";
  std::string ip_address = "127.0.0.1";
  int port = 9000;

  // Creating a sender object.
  UDPSender u = UDPSender(ip_address, port); 

  // Create a buffer with std::vector<char>
  std::vector<char> buffer(message.begin(), message.end());

  // Send it!
  u.send_bytes(buffer);
}
```

## Implementation notes

As you can see in the above example, the UDPSender::send_bytes method accepts a std::vector<char> as the buffer to send. This is common amongst all the tools in this library. Using std::vector keeps our code safe and is more approachable than working with raw buffers.

## Tests

The client/server members of each protocol are tested through the loopback adapter. A simple message is sent over the loopback. Hope to update this with legitimate unit tests at some point.
