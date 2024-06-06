CC := g++
CFLAGS := -std=c++20 -O

TARGET := udp_test

UDP_DIR := ../../../src/udp
UDP_SRC := $(wildcard $(UDP_DIR)/*.cpp)

TEST_SRC := ../loopback_test_udp.cpp

$(TARGET): $(UDP_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET)