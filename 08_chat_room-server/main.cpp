#include "chat_message.h"

#include <boost/asio.hpp>

#include <list>
#include <memory>
#include <iostream>
#include <unordered_set>

#pragma execution_character_set("utf-8")

using boost::asio::ip::tcp;

class chat_participant {
public:
    chat_participant(boost::asio::io_service& io_service)
        : _sock(io_service) {}

    using participant_ptr = std::shared_ptr<chat_participant>;
    
    virtual void start() = 0;
    auto& get_socket() { return chat_participant::_sock; }
    virtual ~chat_participant() {}
    virtual void deliver(const chat_message& msg) = 0;
private:
    tcp::socket _sock;
};

class chat_room {
public:
    chat_room() = default;

    void join(const chat_participant::participant_ptr one_participant) {
        _participant_set.insert(one_participant);
        for (const auto& msg : _recent_msgs) { // 向新用户发送最近的一百条消息
            one_participant->deliver(msg);
        }
    }
    
    void leave(const chat_participant::participant_ptr who) {
        _participant_set.erase(std::move(who));
    }

    void deliver(const chat_message& msg) {
        _recent_msgs.push_back(msg);
        while (_recent_msgs.size() > Max_recent_msgs) {
            _recent_msgs.pop_front();
        }

        for (const auto& participant : _participant_set) {
            participant->deliver(msg);
        }
    }

private:
    static constexpr int Max_recent_msgs = 100; // 保存最近的一百条msg
    std::unordered_set<chat_participant::participant_ptr> _participant_set;
    chat_msg_queue _recent_msgs;
};

class chat_session : public chat_participant
                   , public std::enable_shared_from_this<chat_session>

{
public:
    chat_session() = delete;
    chat_session(boost::asio::io_service& io_service, chat_room& room)
        : chat_participant(io_service)
        , _room(room)
        , _read_msg()
        , _write_msgs() {}

    static participant_ptr create_participant(boost::asio::io_service& io_service, chat_room& room) {
        chat_participant::participant_ptr new_conn = std::shared_ptr<chat_session>(new chat_session(io_service, room));
        return std::move(new_conn);
    }

    virtual void start() override {
        _room.join(static_cast<chat_participant::participant_ptr>(shared_from_this()));
        do_read_header();
    }

private:
    void do_read_header() {
        auto self = shared_from_this();
        boost::asio::async_read(
            chat_participant::get_socket(),
            boost::asio::buffer(_read_msg.data(), chat_message::limit::Header_len),
            [self = std::move(self)](const auto& ec, ::size_t /* len */) {
                if (!ec && self->_read_msg.decode_header()) {
                    self->do_read_body();
                } else {
                    self->_room.leave(self);
                }
            }
        );
    }

    void do_read_body() {
        auto self = shared_from_this();
        boost::asio::async_read(
            chat_participant::get_socket(),
            boost::asio::buffer(_read_msg.body(), _read_msg.get_body_len()),
            [self = std::move(self)](const auto& ec, ::size_t /* len */) {
                if (!ec) {
                    self->_room.deliver(self->_read_msg);
                    self->do_read_header();
                } else {
                    self->_room.leave(self);
                }
            }
        );
    }

    virtual void deliver(const chat_message& msg) override final {
        bool is_writing = !_write_msgs.empty();
        _write_msgs.push_back(std::move(msg));
        if (!is_writing) {
            do_write();
        }
    }

    void do_write() {
        auto self = shared_from_this();
        boost::asio::async_write(
            chat_participant::get_socket(),
            boost::asio::buffer(_write_msgs.front().data(), _write_msgs.front().total_length()),
            [self = std::move(self)](const auto& ec, ::size_t /* len */) {
                if (!ec) {
                    self->_write_msgs.pop_front();
                    if (!self->_write_msgs.empty()) {
                        self->do_write();
                    }
                } else {
                    self->_room.leave(std::move(self));
                }
            }
        );
    }

private:
    chat_room& _room;
    chat_message _read_msg;
    chat_msg_queue _write_msgs;
};

class chat_server {
public:
    chat_server(boost::asio::io_service& io_service, unsigned short port)
        : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)) 
        , _room() { }

    void start() {
        do_accept();
    }

private:
    void do_accept() {
        auto new_participant = chat_session::create_participant(
            static_cast<boost::asio::io_service&>(_acceptor.get_executor().context()),
            _room
        ); // 注册一个session
        _acceptor.async_accept(new_participant->get_socket(), 
            [new_participant, this](const boost::system::error_code& ec) {
                if (!ec) {
                    new_participant->start();
                }

                do_accept();
            }); // 异步accept
    }

private:
    tcp::acceptor _acceptor;
    chat_room _room;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: Chat-room <port> [<port> ...]" << std::endl;
        return -1;
    }

    try {
        boost::asio::io_service io_service;
        std::list<chat_server> servers;
        for (int i = 1; i < argc; i++) {
            servers.emplace_back(chat_server(io_service, ::atoi(argv[i])));
        }

        for (auto& server : servers) {
            server.start();    
        }
        
        io_service.run();
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}