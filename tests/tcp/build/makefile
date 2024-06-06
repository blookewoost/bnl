CC := g++
CFLAGS := -std=c++20 -O

TARGET := tcp_test

# For the TCP test, we will need the TCP tools.
TCP_DIR := ../../../src/tcp
TCP_SRC := $(wildcard $(TCP_DIR)/*.cpp) # match all cpp files

TEST_SRC := ../loopback_test_tcp.cpp

$(TARGET): $(TCP_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET)
