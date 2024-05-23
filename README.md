## Blooke's Networking Library (BNL)

The intention of this project is to create classes that will be readily useful for any networking code.
This way, instead of having to worry about writing out the socket code every time we need to send something over the network, we can just include one of these classes and send whatever data we want. 

## Implementation notes.

Interacting with a socket (sending data or receiving data) via these classes will require the use of a std::vector<char>. This is much easier to use than raw buffers and makes for a clean, modern C++ experience when using BNL.

## Tests

The client/server members of each protocol are tested through the loopback adapter. A simple message is sent over the loopback. Hope to update this with legitimate unit tests at some point.
