#if !defined(CHAT_ROOM_HPP_)
#define CHAT_ROOM_HPP_

#include "common.hpp"
#include "chat_session.hpp"
#include <unordered_set>

class chat_room {
public:
    void join_room(chat_session::session_ptr user);
    void leave_room(chat_session::session_ptr user);
    void deliver_msg(const chat_message& msg);
private:
    enum { RECENT_MSG_AMOUNT = 100 };
    std::unordered_set<chat_session::session_ptr> online_users_;
    msg_queue recent_queue_;
};


#endif // CHAT_ROOM_HPP_
