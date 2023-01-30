#include <array>
#include <memory>
#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    using session_prt = std::shared_ptr<session>;

    tcp::socket& get_socket() { return this->_socket; }

    static session_prt create_session(boost::asio::io_service& io_service) { // 工厂模式
        return session_prt(new session(io_service));
    }

    void start_echo() {
        this->start_receive();
    }

private:
    void start_receive() {
        auto self = shared_from_this();
        _socket.async_read_some(boost::asio::buffer(_arr, Max_len),
            [self = std::move(self)](const boost::system::error_code& ec, std::size_t len) {
                if (!ec) {
                    self->echo_send(len);  
                }
            });
    }

    void echo_send(std::size_t len) {
        auto self = shared_from_this();
        boost::asio::async_write(_socket, boost::asio::buffer(_arr, len),
            [self = std::move(self)](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    self->start_receive();     
                }
            });
    }

    session(boost::asio::io_service& io_service) 
        : _socket(io_service)
        , _arr() { }

private:
    static const int Max_len = 1024;
    tcp::socket _socket;
    std::array<char, Max_len> _arr;
};

class echo_server {
public:
    echo_server(boost::asio::io_service& io_service, short port)
        : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)) { }

    void start() { // server-启动函数
        do_accept();
    }

private:
    void do_accept() {
        auto new_session = 
            session::create_session(
                static_cast<boost::asio::io_context&>(_acceptor.get_executor().context()) // 获取io_service
            );

        _acceptor.async_accept(new_session->get_socket(),
            [new_session, this](const boost::system::error_code& ec) mutable {
                this->accept_handler(ec, std::move(new_session));
            });
        
    }

    void accept_handler(const boost::system::error_code& ec, session::session_prt&& new_session) {
        if (!ec) {
            new_session->start_echo();
        }

        do_accept();
    }

private:
    tcp::acceptor _acceptor;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: Echo-server <port>" << std::endl;
        return -1;
    }
    try {
        boost::asio::io_service io_service;
        echo_server server(io_service, std::atoi(argv[1]));
        server.start();
        std::cout << "Echo-server is started..." << std::endl;
        io_service.run();
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}