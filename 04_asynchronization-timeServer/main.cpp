#include <ctime>

#include <memory>
#include <iostream>
#include <functional>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_dayTime_string() {
    ::time_t now = time(nullptr);
    return ::ctime(&now);
}

class Tcp_connection : public std::enable_shared_from_this<Tcp_connection> {
public:
    using conn_pointer = std::shared_ptr<Tcp_connection>;
    // Tcp_connection类只提供智能指针接口，通过智能指针的方式，实现了当向客户端发送完数据后，socket由析构函数关闭
    // socket是本类的数据成员，本类Dtor时，类成员也会调用其Dtor，socket的析构函数中会调用close()
    static conn_pointer create_tcp_conn(boost::asio::io_service& service) {
        // make_shared局限性: 此处由于Tcp_connection的构造函数是private的，故不能使用make_shared
        // return std::make_shared<Tcp_connection>(service); 
        return conn_pointer(new Tcp_connection(service));
    }

    tcp::socket& getSocket() { return this->_socket; }


    void startSend() {  
        _curTime = make_dayTime_string(); // 服务器获取当前时间
        auto self = this->shared_from_this();
        boost::asio::async_write(_socket, boost::asio::buffer(_curTime), // buffer不含有数据，不确保数据的有效性，一切数据内存均由程序管理
            [self = std::move(self)](const boost::system::error_code& ec, size_t len) {
                self->handler_write(ec, len);
            }
        );
    }

    void handler_write(const boost::system::error_code& ec, size_t) { 
        /*without_do_something*/ 
        std::cout << "send completed!" << std::endl;
    }

    ~Tcp_connection() { std::cout << "close connection!" << std::endl; }

private:
    Tcp_connection(boost::asio::io_service& service)
        : _socket(service)
        , _curTime() {

        }

private:
    tcp::socket _socket;
    std::string _curTime;
};

class Tcp_server {
public:
    Tcp_server(boost::asio::io_service& service)
        : _acceptor(service, tcp::endpoint(tcp::v4(), 13)) {
            // 开始接收连接
            start_accept();
        }

private:
    void start_accept() {
#if BOOST_VERSION >= 107000        
        auto new_connection = Tcp_connection::create_tcp_conn((boost::asio::io_context&)(_acceptor).get_executor().context());
#else
        auto new_connection = Tcp_connection::create_tcp_conn(_acceptor.get_io_service());
#endif
        _acceptor.async_accept(new_connection->getSocket(), 
            [this, new_connection](const boost::system::error_code& ec) {
                this->handler_accept(std::move(new_connection), ec);
            });
    }

void handler_accept(Tcp_connection::conn_pointer conn, const boost::system::error_code& ec) {
    if (!ec) {
        conn->startSend(); // 若成功连接，则开始发送时间
    }
    this->start_accept(); // 无论连接成功与否，开始接收下一个连接
}
    
private:
    tcp::acceptor _acceptor;
};

int main() {
    try {
        boost::asio::io_service io_service;
         Tcp_server server(io_service);
        std::cout << "RUN..." << std::endl;
        io_service.run();
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
} 