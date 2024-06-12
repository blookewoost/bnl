## Blooke's Networking Library (BNL)

Some useful classes for writing networking code.
Example: Sending a UDP packet...

```c++
#include "bnl/include/udp/UDPSender.h"

int main() {
  
  std::string message = "Hello from UDPSender!";
  std::string ip_address = "127.0.0.1";
  int port = 9000;

  // Creating a sender object.
  UDPSender u = UDPSender(ip_address, port); 

  // Create a buffer with std::vector<char>
  std::vector<char> buffer(message.begin(), message.end());
}
```

## Implementation notes.

Interacting with a socket (sending data or receiving data) via these classes will require the use of a std::vector<char>. This is much easier to use than raw buffers and makes for a clean, modern C++ experience when using BNL.

## Tests

The client/server members of each protocol are tested through the loopback adapter. A simple message is sent over the loopback. Hope to update this with legitimate unit tests at some point.
