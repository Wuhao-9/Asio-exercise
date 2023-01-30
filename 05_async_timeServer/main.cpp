#include <ctime>

#include <memory>
#include <iostream>
#include <functional>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string get_current_time() {
    ::time_t now = time(nullptr);
    return static_cast<std::string>(ctime(&now));
}

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    using conn_ptr = std::shared_ptr<tcp_connection>;

    static conn_ptr create_conn(boost::asio::io_service& io) {
        return conn_ptr(new tcp_connection(io));
    }

    tcp::socket& socket() { return _socket; }

    void start_send() {
        _msg = get_current_time();
        auto self = shared_from_this();
        boost::asio::async_write(_socket, boost::asio::buffer(_msg),
            [self = std::move(self)](const boost::system::error_code& ec, ::size_t len) {
                self->write_handler(ec, len);
            });
    }

private:
    tcp_connection(boost::asio::io_service& io_service) 
        : _socket(io_service) { }

    void write_handler(const boost::system::error_code&, ::size_t) { std::cout << "send completed!" << std::endl; }
private:
    boost::asio::ip::tcp::socket _socket;
    std::string _msg;
};

class tcp_server {
public:
    tcp_server(boost::asio::io_service& io_service) 
        : _acceptor(io_service, tcp::endpoint(tcp::v4(), 13)) {
            start_accept();
        }

private:
    void start_accept() {
        tcp_connection::conn_ptr new_conn = tcp_connection::create_conn((boost::asio::io_context&)_acceptor.get_executor().context());
        _acceptor.async_accept(new_conn->socket(), 
            [this, new_conn](auto err) {
                this->accept_handler(new_conn, err);
            });
    }

    void accept_handler(tcp_connection::conn_ptr new_conn, const boost::system::error_code& err) {
        if (!err) {
            new_conn->start_send();
        }

        start_accept();
    }

private:
    tcp::acceptor _acceptor;
};

int main() {
    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service);
        io_service.run();
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
    }    
    return 0;
}