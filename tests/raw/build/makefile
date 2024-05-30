CC := g++
CFLAGS := -std=c++20 -O

TARGET := rs_test

# For the RawSocket test, we will need the UDP, RawSocket, and IPv4Packet tools.
UDP_DIR := ../../../src/udp
UDP_SRC := $(wildcard $(UDP_DIR)/*.cpp) # match all cpp files

RS_DIR := ../../../src/raw
RS_SRC := $(wildcard $(RS_DIR)/*.cpp)

PACKET_DIR := ../../../src/packet
PACKET_SRC := $(wildcard $(PACKET_DIR)/*.cpp)

TEST_SRC := ../test_RawSocket.cpp

$(TARGET): $(UDP_SRC) $(RS_SRC) $(PACKET_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET)