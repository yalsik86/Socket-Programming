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

void session(tcp::socket socket, ssl::context &ssl_ctx) {
    websocket::stream<ssl::stream<tcp::socket>> ws(std::move(socket), ssl_ctx);
    ws.next_layer().handshake(ssl::stream_base::server);
    ws.accept();

    beast::flat_buffer buffer;
    ws.read(buffer);

    auto msg = beast::buffers_to_string(buffer.data());
    std::cout << "Client: " << msg << "\n";

    auto data = "[+] Received: " + msg;

    ws.text(ws.got_text());
    ws.write(net::buffer(data));
}

int main() {
    net::io_context ioc;
    ssl::context ssl_ctx(ssl::context::tls_server);
    ssl_ctx.use_certificate_chain_file("server.crt");
    ssl_ctx.use_private_key_file("server.key", ssl::context::pem);

    auto endpoint = tcp::endpoint(tcp::v4(), 8443);
    tcp::acceptor acceptor(ioc, endpoint);
    std::cout << "WSS server listening on wss://localhost:8443\n";

    tcp::socket socket(ioc);
    acceptor.accept(socket);
    session(std::move(socket), std::ref(ssl_ctx));
}
