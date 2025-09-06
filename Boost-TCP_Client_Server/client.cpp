#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using boost::asio::ip::tcp;

void session(tcp::socket socket);

int main() {
    try {
        io_context io;

        tcp::resolver resolver(io);
        auto endpoints = resolver.resolve("127.0.0.1", "8000");

        tcp::socket socket(io);
        connect(socket, endpoints);

        std::cout << "connected to server\n";

        session(std::move(socket));
    }
    catch(const std::exception& e) {
        std::cerr << "[Exception]: " << e.what() << '\n';
    }  
}



void session(tcp::socket socket) {
    try {
        while(true) {
            std::cout << "enter message: ";
            std::string msg;
            std::getline(std::cin, msg);
            write(socket, buffer(msg));

            if(msg == "exit") {
                std::cout << "client exit\n";
                break;
            }

            char data[1024];
            std::size_t len = socket.read_some(buffer(data));
            auto received = std::string(data, len);

            std::cout << "message from server: " << received << "\n";
            if(received == "exit") {
                std::cout << "client exit\n";
                break;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "session ended: " << e.what() << "\n";
    }
}
