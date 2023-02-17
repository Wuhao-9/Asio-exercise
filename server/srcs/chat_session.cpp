#include "chat_session.hpp"
#include "chat_room.hpp"
#include "msg_format.pb.h"

chat_session::chat_session(boost::asio::io_service& io_service, chat_room& room)
    : chat_participant()
    , sock_(io_service)
    , room_(room)
{
    
}

void chat_session::connected_handler() {
    room_.join_room(shared_from_this());
    set_name(sock_.remote_endpoint().address().to_string());
    do_read_header();
}

void chat_session::do_read_header() {
    boost::asio::async_read(sock_, boost::asio::buffer(recv_buffer_.data(), chat_message::MSG_HEADER_LENGTH),
        [self = shared_from_this()](const boost::system::error_code& ec, const std::size_t transfered_length) {
            if (!ec && self->recv_buffer_.decoding_received_header(transfered_length)) {
                self->do_read_body();
            } else {
                self->room_.leave_room(std::move(self));
            }
        });
}

void chat_session::do_read_body() {
    boost::asio::async_read(sock_, boost::asio::buffer(recv_buffer_.body(), recv_buffer_.get_body_size()),
        [self = shared_from_this()](const auto& ec, const std::size_t transfered_length) {
            if (!ec) {
                self->parse_recv_content();
                self->do_read_header();
            } else {
                self->room_.leave_room(std::move(self));
            }
        });
}

bool chat_session::fill_protoObj(google::protobuf::Message* obj) {
    std::string context(recv_buffer_.body(), recv_buffer_.body() + recv_buffer_.get_body_size());
    return obj->ParseFromString(context);
}

const chat_message chat_session::build_ReplyPackage(const std::string& msg_content) {
    msg_protocol::server_reply reply;
    reply.set_user_name(user_name_);
    reply.set_info(msg_content);

    std::string result_str;
    if (reply.SerializeToString(&result_str)) {
        
        return chat_message(msg_type::ROOM_INFO, result_str);
    }
    throw std::runtime_error("serialization fail!");
}

/**
 * @brief 可以试着用template改进 
 * 
 */
bool chat_session::parse_recv_content() {
    if (recv_buffer_.get_msg_type() == msg_type::BIND_NAME) {
        msg_protocol::set_user_name deserializer;
        if (fill_protoObj(&deserializer)) {
            user_name_ = deserializer.name();
            return true;
        }
    } else if (recv_buffer_.get_msg_type() == msg_type::CHAT_PUBLIC) {
        msg_protocol::chat_publice deserializer;
        if (fill_protoObj(&deserializer)) {
            std::string msg_content = deserializer.msg();
            chat_message reply_package;
            try {
                reply_package = build_ReplyPackage(std::move(msg_content));
            } catch (std::runtime_error& err) {
                std::cerr << "Build Reply package fail!" << std::endl;
                return false;
            }
            room_.deliver_msg(std::move(reply_package));
            return true;
        }   
    }
    return false;
}

void chat_session::deliver(const chat_message& msg) {
    bool no_working = queue_.empty();
    queue_.push_back(msg);
    if (no_working) {
        send_to_client();
    }
}

void chat_session::send_to_client() {
    boost::asio::async_write(sock_, boost::asio::buffer(queue_.front().data(), queue_.front().get_total_size()),
        [self = shared_from_this()](const auto& ec, const std::size_t transfered_length) {
            self->send_handler(ec, transfered_length);
        });
}

void chat_session::send_handler(const boost::system::error_code& ec, const std::size_t transfered_length) {
    std::cout << "send sucess..." << std::endl;
    if (!ec) {
        queue_.pop_front();
        if (!queue_.empty()) {
            send_to_client();
        }
    } else {
        room_.leave_room(shared_from_this());
    }
}

chat_session::session_ptr chat_session::create_newConn(boost::asio::io_context& io_service, chat_room& room) {
    return session_ptr(new chat_session(io_service, room));
}