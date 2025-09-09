#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <iostream>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace ssl = boost::asio::ssl;
namespace websocket = boost::beast::websocket;
using boost::asio::ip::tcp;

int main() {
    net::io_context ioc;
    ssl::context ssl_ctx(ssl::context::tls_client);
    ssl_ctx.set_default_verify_paths();

    tcp::resolver resolver(ioc);
    websocket::stream<ssl::stream<tcp::socket>> ws(ioc, ssl_ctx);

    auto endpoints = resolver.resolve("127.0.0.1", "8443");
    net::connect(ws.next_layer().next_layer(), endpoints.begin(), endpoints.end());

    ws.next_layer().handshake(ssl::stream_base::client);
    ws.handshake("127.0.0.1", "/");

    ws.write(net::buffer("Hellow mane over TLS!"));

    beast::flat_buffer buffer;
    ws.read(buffer);
    std::cout << "Server: " << beast::make_printable(buffer.data()) << "\n";
}
