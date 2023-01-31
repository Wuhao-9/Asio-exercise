#if !defined(STRUCT_HEADER_H_)
#define STRUCT_HEADER_H_

#include <string>

enum class msg_type : char {
    ROOM_INFO = 1,
    BIND_NAME,
    CHAT_MSG,
};

struct header {
    int body_size;
    msg_type type;
};

struct bindName {
    char name[32];
    int name_len;
};

struct chatMessage {
    char msg;
    int msg_len;
};

struct roomInfo {
    bindName name_info;
    chatMessage information;
};

#endif // STRUCT_HEADER_H_
