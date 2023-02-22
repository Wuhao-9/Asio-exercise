#if !defined(CHAT_ROOM_HPP_)
#define CHAT_ROOM_HPP_

#include "common.hpp"
#include "chat_session.hpp"
#include <boost/asio.hpp>
#include <unordered_set>

class chat_room {
public:
    chat_room(boost::asio::io_service& io_service)
        : strand_(io_service) { }
    void join_room(chat_session::session_ptr user);
    void leave_room(chat_session::session_ptr user);
    void deliver_msg(const chat_message& msg);
private:
    enum { RECENT_MSG_AMOUNT = 100 };
    std::unordered_set<chat_session::session_ptr> online_users_;
    msg_queue recent_queue_;
    boost::asio::io_service::strand strand_;
};


#endif // CHAT_ROOM_HPP_
