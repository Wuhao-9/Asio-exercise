#if !defined(CHAT_PARTICIPANT_HPP_)
#define CHAT_PARTICIPANT_HPP_
#include "chat_message.hpp"
#include <string>


class chat_participant {
public:
    chat_participant() = default; 
    void set_name(const std::string& name) { user_name_ = name; }
    virtual void deliver(const chat_message&) = 0;
protected:
    std::string user_name_;
};

#endif // CHAT_PARTICIPANT_HPP_