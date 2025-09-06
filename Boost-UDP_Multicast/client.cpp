#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using boost::asio::ip::udp;

int main() {
    try {
        io_context ioc;
        udp::endpoint listen_endpoint(udp::v4(), 9000);
        udp::socket socket(ioc, listen_endpoint);

        socket.set_option(ip::multicast::join_group(
            ip::make_address_v4("239.255.255.1")
        ));

        char data[1024];
        udp::endpoint sender_endpoint;
        while(true) {
            size_t len = socket.receive_from(buffer(data), sender_endpoint);
            std::cout << "[+] Received: " << std::string(data, len) << "\n";
        }
    }
    catch(const std::exception& e) {
        std::cerr <<"[-] Exception: " << e.what() << "\n";
    }
}
