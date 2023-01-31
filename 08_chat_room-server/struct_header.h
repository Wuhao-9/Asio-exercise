#if !defined(STRUCT_HEADER_H_)
#define STRUCT_HEADER_H_

#include <string>

enum class msg_type : char {
    ROOM_INFO = 0,
    BIND_NAME,
    CHAT_MSG
};

struct header {
    ::size_t body_size;
    msg_type type;
};

struct bindName {
    static constexpr int Max_name_length = 32; 
    char name[Max_name_length];
    ::size_t name_len;
};

struct chatPublic {
    static constexpr int Max_msg_length = 256; 
    char msg[Max_msg_length];
    ::size_t msg_len;
};

struct roomInfo {
    bindName name_info;
    chatPublic information;
};

bool parseMessage(const std::string& input, msg_type& type, std::string& output_buf);

#endif // STRUCT_HEADER_H_
