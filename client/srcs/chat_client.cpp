#include "msg_format.pb.h"
#include "chat_client.hpp"
#include <iostream>
chat_client::chat_client(boost::asio::io_service& io_service, const tcp::resolver::iterator& endpoint_iterator) 
    : sock_(io_service)
    , remote_endpoint_(endpoint_iterator)
    , recv_buffer_()
    , send_queue_() { }


void chat_client::send_to_serve(const chat_message& msg) {
    bool no_woring = send_queue_.empty();
    send_queue_.push_back(msg);
    if (no_woring) {
        start_send_queue_msgs();
    }
}

void chat_client::start_send_queue_msgs() {
    boost::asio::async_write(sock_, boost::asio::buffer(send_queue_.front().data(), send_queue_.front().get_total_size()),
        [this](const auto& ec, const std::size_t /*len*/) {
            if (!ec) {
                send_queue_.pop_front();
                if (!send_queue_.empty()) {
                    start_send_queue_msgs();
                }
            } else {
                std::cerr << ec.message() << std::endl;
            }
    });
}

void chat_client::recv_header() {
    boost::asio::async_read(this->sock_, boost::asio::buffer(this->recv_buffer_.data(), chat_message::MSG_HEADER_LENGTH),
    [this](const auto& ec, const std::size_t transfered_length) {
        if (!ec && recv_buffer_.decoding_received_header(transfered_length)) {
            recv_body();
        } else {
            std::cerr << ec.message() << std::endl;
        }
    });
}

void chat_client::recv_body() {
    boost::asio::async_read(this->sock_, boost::asio::buffer(recv_buffer_.body(), recv_buffer_.get_body_size()),
        [this](const auto& ec, const std::size_t transfered_length) {
            if (!ec) {
                msg_protocol::server_reply deserializer;
                std::string str(recv_buffer_.body(), recv_buffer_.body() + recv_buffer_.get_body_size());
                if (!deserializer.ParseFromString(str)) {
                    std::cerr << "Deserialize failure!" << std::endl;
                }
                std::cout << "[" << deserializer.user_name() << "] Say: " << deserializer.info() << std::endl;
                recv_header();
            } else {
                std::cerr << ec.message() << std::endl;
            }
        });
}

void chat_client::connect_to_server() {
    boost::asio::async_connect(sock_, remote_endpoint_,
    [this](const auto& ec, tcp::resolver::iterator /*it*/) {
        if (!ec) {
            std::cout << "<<<<< connect succeed!\n";
            this->recv_header();
        } else {
            std::cerr << ec.message() << std::endl;
        }
    });
}