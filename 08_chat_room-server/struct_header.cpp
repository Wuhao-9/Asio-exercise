#include "struct_header.h"

/**
 * @brief 解析用户的输入
 * 
 * @param user_input 
 * @param type 
 * @param output_buf 
 * @return true 
 * @return false 
 */
bool parseMessage(const std::string& uset_input, msg_type& type, std::string& output_buf) { 
    auto pos = uset_input.find_first_of(" ");
    if (pos == std::string::npos) 
        return false;
    auto command = uset_input.substr(0, pos);
    if (command == "/bindName") {
        std::string name = uset_input.substr(pos + 1);
        if (name.size() > static_cast<::size_t>(limit::Max_name_length)) {
            return false;
        }

        type = msg_type::BIND_NAME;
        msg_protocol_pb::set_user_name serialize_obj;
        serialize_obj.set_name(name);
        auto ok = serialize_obj.SerializeToString(&output_buf);
        return ok;
    } else if (command == "/chat") {
        std::string msg = uset_input.substr(pos + 1);
        if (msg.size() > static_cast<::size_t>(limit::Max_msg_length)) {
            return false;
        }

        type = msg_type::CHAT_MSG;
        msg_protocol_pb::chat_publice serialize_obj;
        serialize_obj.set_msg(msg);
        auto ok = serialize_obj.SerializeToString(&output_buf);
        return ok;
    }
}
