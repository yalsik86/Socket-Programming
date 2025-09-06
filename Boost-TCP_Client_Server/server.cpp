#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using boost::asio::ip::tcp;

void session(tcp::socket socket);

int main() {
    try {
        io_context io;
        auto endpnt = tcp::endpoint(tcp::v4(), 8000);
        tcp::acceptor accpetor(io, endpnt);

        std::cout << "Server listening on port 8000...\n";

        tcp::socket socket(io);
        accpetor.accept(socket);

        std::cout << "server accept successful\n";
        session(std::move(socket));
    }
    catch(const std::exception& e) {
        std::cerr <<"[Exception]: " << e.what() << '\n';
    }
}



void session(tcp::socket socket) {
    try {
        while(true) {
            char data[1024];
            std::size_t len = socket.read_some(buffer(data));
            auto received = std::string(data, len);

            std::cout << "message from client: " << received << "\n";
            if(received == "exit") {
                std::cout << "server exit\n";
                break;
            }

            std::cout << "enter message: ";
            std::string msg;
            std::getline(std::cin, msg);
            write(socket, buffer(msg));

            if(msg == "exit") {
                std::cout << "server exit\n";
                break;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "session ended: " << e.what() << "\n";
    }
}
