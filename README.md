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

#NOTE:

As you can see in the above example, the UDPSender::send_bytes method accepts a std::vector<char> as the buffer to send. This is common amongst all the tools in this library. Using std::vector keeps our code safe and is more approachable than working with raw buffers. 

Continuing, here's what the code for a TCP Client/Server pair would look like...

## TCPListener (Server)

```c++
#include "bnl/include/tcp/TCPListener.h"

void main() {
  // Create a listening TCP object...
  TCPListener l = TCPListener(9000); // port number
  if (listener.start_listening()) {
  // obtain a socket file descriptor by accepting a connection.
    int cli_sock = listener.accept_connection();
    // How many bytes do we want to read?
    ssize_t buffersize = 1024;
    // Receive bytes from the socket
    std::vector<char> buffer = listener.receive_bytes(cli_sock, buffersize);

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

        // what a lovely method. thanks std::vector :)
        data.assign(message.begin(), message.end());
        if (!client.send_bytes(data)) {
            printf("Something went wrong!");
        }

    }

}
```

These objects should prove useful for writing some pretty solid networking code. Of course, there's always room for improvement! 

and one more thing, the RawSocket... this is my personal favorite. Hoping to go into a little more detail about that one.

## Tests

The client/server members of each protocol are tested through the loopback adapter. A simple message is sent over the loopback. Hope to update this with legitimate unit tests at some point.