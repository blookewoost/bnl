## Blooke's Networking Library (BNL)

Networking utilities for common socket operations. Use BNL for any basic TCP/UDP networking code, or to create a RawSocket and explore the network stack with the /packet utilities. 

Example: Sending a UDP Packet

```c++
#include "bnl/include/udp/UDPSender.h"

int main() {
  
  std::string message = "Hello from UDPSender!";
  std::string ip_address = "127.0.0.1";
  int port = 9000;

  // Creating a sender object.
  UDPSender u = UDPSender(ip_address, port); 

  // Create a buffer with std::vector
  std::vector<char> buffer(message.begin(), message.end());

  // Send it!
  u.send_bytes(buffer);
}
```

#NOTE:

As you can see in the above example, the UDPSender::send_bytes method accepts a std::vector<char> as the buffer to send. This is common amongst all the tools in this library. Using std::vector keeps our code safe and is more approachable than working with raw buffers. 

Continuing, here's what the code for a TCP Client/Server pair would look like...

## TCPListener (Server)

```c++
#include "bnl/include/tcp/TCPListener.h"

void server() {
  // Create a listening TCP object...
  TCPListener l = TCPListener(9000); // port number
  if (l.start_listening()) {
  // obtain a socket file descriptor by accepting a connection.
    int cli_sock = l.accept_connection();
    // How many bytes do we want to read?
    ssize_t buffersize = 1024;
    // Receive bytes from the socket
    std::vector<char> buffer = l.receive_bytes(cli_sock, buffersize);

    // What did they say? 
    std::string message(buffer.begin(), buffer.end());
    printf("Received a message from the client:\n %s", message.c_str());
  }

}

```

and of course, the client... 

## TCPClient (Client)

```c++

#include "bnl/include/tcp/TCPClient.h"

void client() {
    std::string ip = "127.0.0.1";
    TCPClient client = TCPClient(ip, 9000);

    if (client.connect_to_listener()) {
        ssize_t buffersize = 1024;
        std::string message = "Hello from the client!";
        std::vector<char> data;

        data.assign(message.begin(), message.end());
        if (!client.send_bytes(data)) {
            printf("Something went wrong!");
        }

    }

}
```

These objects should prove useful for writing some pretty solid networking code. Of course, there's always room for improvement! 
and one more thing, the RawSocket... Hoping to go into a little more detail about that one.

```c++

#include "bnl/include/raw/RawSocket.h"

int main() {
  RawSocket r = RawSocket("lo") // provide an interface to open the raw socket on
  std::size_t buffersize = 1024; // how many bytes to read?

  std::vector<char> buf = r.read(buffersize);
  //now you can do whatever you want with these bytes!
}
```

Once you have received packets from a raw socket, you can use the packet utilities in this library (see /include/packet & /src/packet) to create Packet objects of the specified protocol. 

For an example of this, check out /tests/raw/test_RawSocket.cpp

## Tests

The client/server members of each protocol are tested through the loopback adapter. A simple message is sent over the loopback. Hope to update this with legitimate unit tests at some point.