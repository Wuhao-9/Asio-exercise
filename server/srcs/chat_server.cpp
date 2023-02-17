#include "chat_server.hpp"

chat_server::chat_server(boost::asio::io_context& io_context,
                    const std::string& host, const std::string& port)
    : room_() 
    , acceptor_(io_context) {
        tcp::resolver resolver(io_context);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        acceptor_.open((*endpoint_iterator).endpoint().protocol());
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind((*endpoint_iterator).endpoint());
        acceptor_.listen();
    }

chat_server::chat_server(boost::asio::io_service& io_service, unsigned short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    , room_() { }

void chat_server::do_accept() {
    auto new_conn = chat_session::create_newConn(get_io_context(), room_);
    acceptor_.async_accept(
        new_conn->get_socket(),
        [new_conn, this](const auto& ec) {
            if (!ec) {
                new_conn->connected_handler();
            } else {
                std::cout << "![" << ec.value() << "]" << ec.message() << std::endl;
            }
            do_accept();
        });
}