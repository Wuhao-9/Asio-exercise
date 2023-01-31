#include "struct_header.h"

// msg format: 请求关键字 消息体

/**
 * @brief 解析客户端输入是否有效, 若有效则序列化为二进制
 * @param input 客户端输入的cmd
 * @param type 
 * @param output_buf 
 */
bool parseMessage(const std::string& input, msg_type& type, std::string& output_buf) {
    auto pos = input.find_first_of(" ");
    if (pos == std::string::npos || pos == 0)
        return false;
    auto command = input.substr(0, pos); // 获取请求关键字
    if (command == "/bindName") {
        std::string name = input.substr(pos + 1); // 获取消息体
        if (name.size() > bindName::Max_name_length) {
            return false;
        }

        type = msg_type::BIND_NAME;
        bindName bindInfo; // 绑定信息
        bindInfo.name_len = name.size();
        ::memcpy(bindInfo.name, name.data(), name.size());
        auto buffer = reinterpret_cast<const char*>(&bindInfo); 
        output_buf.assign(buffer, buffer + sizeof(bindInfo)); // 将结构体转换为binary编码
        return true;

    } else if (command == "/chat") {
        std::string msg = input.substr(pos + 1);
        if (msg.size() > chatPublic::Max_msg_length) {
            return false;
        }
        
        type = msg_type::CHAT_MSG;
        chatPublic chat;
        chat.msg_len = msg.size();
        ::memcpy(chat.msg, msg.data(), msg.size());
        auto buffer = reinterpret_cast<const char*>(&chat);
        output_buf.assign(buffer, buffer + sizeof(chatPublic));
        return true;
    }
    return false; // 请求关键字不正确
}
