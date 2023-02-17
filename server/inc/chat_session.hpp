#if !defined(CHAT_SESSION_HPP_)
#define CHAT_SESSION_HPP_

#include "chat_participant.hpp"
#include "chat_message.hpp"
#include "msg_format.pb.h"
#include "common.hpp"
#include <memory>
class chat_room;

class chat_session : public chat_participant
                , public std::enable_shared_from_this<chat_session>
{
public:
    using session_ptr = std::shared_ptr<chat_session>;
    static session_ptr create_newConn(boost::asio::io_context&, chat_room&);
    tcp::socket& get_socket() { return sock_; }
    virtual void deliver(const chat_message&) override;
    void connected_handler();
private:
    chat_session() = delete;
    chat_session(boost::asio::io_service& io_service, chat_room& room);
    void send_to_client();
    void send_handler(const boost::system::error_code& ec, const std::size_t transfered_length);
    void do_read_header();
    void do_read_body();
    bool fill_protoObj(google::protobuf::Message* obj);
    const chat_message build_ReplyPackage(const std::string& msg_content);
    bool parse_recv_content();
private:
    tcp::socket sock_;
    chat_room& room_;
    chat_message recv_buffer_;
    msg_queue queue_;  // 为保证消息按序发送
};

#endif // CHAT_SESSION_HPP_