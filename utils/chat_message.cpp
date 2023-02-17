#include "chat_message.hpp"
#include "msg_format.pb.h"
#include <iostream>

bool chat_message::parse_input_AND_pack(const std::string& user_input) {
     auto pos = user_input.find_first_of(" ");
    if (pos == std::string::npos) {
        return false;
    }
    auto command = user_input.substr(0, pos);
    if (command == "/bindName" || command == "/bindname") {
        std::string name = user_input.substr(pos + 1);
        if (name.size() > chat_message::limit::NAME_MAX_LENGTH) {
            std::cerr << "Invalid name, it`s too long! (maximum length: " << chat_message::NAME_MAX_LENGTH << ")" << std::endl;
            return false;
        }

        msg_protocol::set_user_name serializer;
        serializer.set_name(name);
        std::string body_content;
        if (!serializer.SerializeToString(&body_content)) {
            std::cerr << "serialize fail" << std::endl;
            return false;
        }
        this->fill_package(body_content, msg_type::BIND_NAME);
        return true;
    } else if (command == "/chat") {
        std::string msg = user_input.substr(pos + 1);
        if (msg.size() > chat_message::limit::MSG_MAX_BODY_LENGTH) {
            std::cerr << "Invalid message, it`s too long! (maximum length: " << chat_message::MSG_MAX_BODY_LENGTH << ")" << std::endl;
            return false;
        }

        msg_protocol::chat_publice serializer;
        serializer.set_msg(msg);
        std::string body_content;
        if (!serializer.SerializeToString(&body_content)) {
            std::cerr << "serialize fail" << std::endl;
            return false;
        }
        this->fill_package(body_content, msg_type::CHAT_PUBLIC);
        return true;
    } else {
        std::cerr << "The Command is invalid, Please try again!" << std::endl;
    }
    return false;
}

chat_message::chat_message(const msg_type type, const std::string& info) 
    : msg_header_(type, info.size())
{
    ::mempcpy(data(), &msg_header_, MSG_HEADER_LENGTH);
    ::memcpy(body(), info.data(), info.size());
}