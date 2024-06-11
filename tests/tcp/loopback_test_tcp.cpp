#include "../../include/tcp/TCPClient.h"
#include "../../include/tcp/TCPListener.h"
#include <thread>
#include <chrono>

void server() {
    TCPListener listener = TCPListener(9000);

    if (listener.start_listening()) {
        int cli_sock = listener.accept_connection();
        ssize_t buffersize = 1024;
        std::vector<char> buffer = listener.receive_bytes(cli_sock, buffersize);

        std::string message(buffer.begin(), buffer.end());
        printf("Received a message from the client:\n %s", message.c_str());
    }

    
}

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

int main() {
    std::thread listener_thread(server);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread client_thread(client);

    listener_thread.join();
    client_thread.join();
}