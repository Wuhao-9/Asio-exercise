#include "chat_room.hpp"

void chat_room::deliver_msg(const chat_message& msg) {
    strand_.dispatch([this, &msg]() {
            recent_queue_.emplace_back(msg);
            while (recent_queue_.size() > RECENT_MSG_AMOUNT) {
                recent_queue_.pop_front();
            }
        }
    );
    for (const auto& user : online_users_) {
        user->deliver(msg);
    }
}

void chat_room::join_room(chat_session::session_ptr user) {
    strand_.dispatch([this, &user] {
        online_users_.emplace(user);
    });
    for (const auto& msg : recent_queue_) {
        user->deliver(msg);
    }
}

void chat_room::leave_room(chat_session::session_ptr who) {
    strand_.dispatch([this, &who]() {
        online_users_.erase(std::move(who));
    });
}