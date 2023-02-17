#if !defined(CHAT_SERVER_HPP_)
#define CHAT_SERVER_HPP_

#include "chat_session.hpp"
#include "chat_room.hpp"

class chat_server {
public:
    chat_server(boost::asio::io_context&, const std::string& , const std::string& );
    chat_server(boost::asio::io_service& io_service, unsigned short port);
    void start() { do_accept(); }
private:
    void do_accept();
    boost::asio::io_context& get_io_context() { return static_cast<boost::asio::io_service&>(acceptor_.get_executor().context()); };

private:
    tcp::acceptor acceptor_;
    chat_room room_;
};

#endif // CHAT_SERVER_HPP_