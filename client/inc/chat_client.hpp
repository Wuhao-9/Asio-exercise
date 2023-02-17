#if !defined(CHAT_CLIENT_HPP_)
#define CHAT_CLIENT_HPP_

#include "common.hpp"
#include "chat_message.hpp"
#include <boost/asio.hpp>
class chat_client {
public:
    chat_client(boost::asio::io_service& io_service, const tcp::resolver::iterator& endpoint);

    void send_to_serve(const chat_message& msg);


    void start() {
        connect_to_server();
    }
    
private:
    void recv_header();
    void recv_body();
    void start_send_queue_msgs();
    void connect_to_server();
    
private:
    tcp::socket sock_;
    chat_message recv_buffer_;
    msg_queue send_queue_;
    tcp::resolver::iterator remote_endpoint_;
};

#endif // CHAT_CLIENT_HPP_

