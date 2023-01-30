#include "chat_message.h"

#include <boost/asio.hpp>

#include <iostream>
#include <thread>

#include <winerror.h>

using boost::asio::ip::tcp;
class chat_client {
public:
    chat_client(boost::asio::io_service& io_service, const tcp::resolver::iterator& endpoint_it)
        : _io_service(io_service)
        , _sock(io_service)
        , _write_queue()
        , _read_msg() {
            do_connect(endpoint_it);
        }

    void close_socket() {
        _io_service.post( // 保证由io_service管理，防止并行的访问临界资源
            [this]() {
                boost::system::error_code err;
                _sock.shutdown(tcp::socket::shutdown_both, err); // ignore error_code
                _sock.close(err);
                std::cout << err.what() << std::endl;
            }
        );
    }

    void write(const chat_message& msg) {
        _io_service.post(
            [this, msg]() { // 保证由io_service管理，防止并行的访问临界资源
            bool is_writing = !_write_queue.empty();
            _write_queue.emplace_back(msg);
            if (!is_writing) {
                write_to_server();
            }
        });
    }   

private:
    void write_to_server() {
        boost::asio::async_write(
            _sock,
            boost::asio::buffer(_write_queue.front().data(), _write_queue.front().total_length()),
            [this](const auto& err, ::size_t /* len */) {
                if (!err) {
                    _write_queue.pop_front();
                    if (!_write_queue.empty()) {
                        write_to_server();
                    }
                } else if (err != boost::asio::error::operation_aborted) { 
                    std::cerr << "[" << __LINE__ << "] " << "!: " << err.what() << std::endl;
                    _sock.shutdown(tcp::socket::shutdown_both);
                    _sock.close();
                } else {
                    std::cerr << "[" << __LINE__ << "] " << "!!!: " << err.what() << std::endl;
                }
            }
        );
    }

    void do_connect(const tcp::resolver::iterator& endpoint_it) {
        boost::asio::async_connect(
            _sock,
            endpoint_it,
            [this](const boost::system::error_code& err, tcp::resolver::iterator /*it*/) {
                if (!err) {
                    std::cout << "<<<<< connect succeed!\n";
                    this->parse_header();
                } else {
                    std::cerr << err.what() << std::endl;
                }
            }
        );
    }

    void parse_header() {
        _sock.async_receive(boost::asio::buffer(_read_msg.data(), chat_message::limit::Header_len), 
            [this](const boost::system::error_code& err, ::size_t /* len */) {
                if (!err && this->_read_msg.decode_header()) {
                    parse_body();
                } else if (err != boost::asio::error::operation_aborted 
                       /*&& err.value() != boost::winapi::ERROR_CONNECTION_ABORTED_*/) { // “本端关闭套接字”的system错误码
                    std::cerr << "[" << __LINE__ << "] " << "!: " << err.what() << std::endl;
                    _sock.shutdown(tcp::socket::shutdown_both);
                    _sock.close();
                }
            });
    }

    void parse_body() {
        boost::asio::async_read(
            _sock,
            boost::asio::buffer(_read_msg.body(), this->_read_msg.get_body_len()),
            [this](const boost::system::error_code& err, ::size_t /* len */) {
                if (!err) {
                    std::cout.write(_read_msg.body(), _read_msg.get_body_len()) << std::endl;
                    parse_header();
                } else if (err != boost::asio::error::operation_aborted) { 
                    std::cerr << "！:  " << err.what() << std::endl;
                    _sock.shutdown(tcp::socket::shutdown_both);
                    _sock.close();
                }
            }
        );
    }

private:
    boost::asio::io_service& _io_service;
    tcp::socket _sock;
    chat_message _read_msg;
    chat_msg_queue _write_queue;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Chat-client <host> <port>" << std::endl;
        return -1;
    }

    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(argv[1], argv[2]);
        chat_client client_instance(io_service, endpoint_iterator);
        
        std::thread t([&io_service]() { 
            try {
                io_service.run();
            } catch (const std::exception& e) {
                std::cerr << __LINE__ << e.what() << '\n';
            }
        });
        
        std::array<char, chat_message::limit::Max_body_len + 1> line;
        while (std::cin.getline(line.data(), chat_message::limit::Max_body_len + 1)) {
            chat_message cur_msg;
            cur_msg.set_body_len(::strlen(line.data()));
            ::memcpy(cur_msg.body(), line.data(), cur_msg.get_body_len());
            cur_msg.encode_header();
            client_instance.write(cur_msg);
        }
        
        client_instance.close_socket();
        t.join();
    } catch (const std::exception& e) {
        std::cerr << __LINE__ << e.what() << '\n';
    }
    return 0;
}