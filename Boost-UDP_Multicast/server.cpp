#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace boost::asio;
using boost::asio::ip::udp;

int main() {
    try {
        io_context ioc;
        udp::endpoint endpoint(udp::v4(), 0);
        udp::socket socket(ioc, endpoint);

        udp::endpoint multicast_endpoint(ip::make_address_v4("239.255.255.1"), 9000);

        int count = 0;
        while(true) {
            std::string msg = "[Hello " + std::to_string(count++) + "]\n";
            socket.send_to(buffer(msg), multicast_endpoint);
            std::cout << "[+] Multicast msg sent\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } 
    catch (const std::exception &e) {
        std::cerr << "[-] Exception: " << e.what() << "\n";
    }
}
