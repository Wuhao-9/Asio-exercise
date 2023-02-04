#if !defined(STRUCT_HEADER_H_)
#define STRUCT_HEADER_H_

#include <string>
#include "msg_protocol.pb.h"

enum class msg_type : char {
    ROOM_INFO = 0,
    BIND_NAME,
    CHAT_MSG
};

enum class limit {
    Max_name_length = 32,
    Max_msg_length = 256
};

struct header {
    ::size_t body_size;
    msg_type type;
};

bool parseMessage(const std::string& input, msg_type& type, std::string& output_buf);

#endif // STRUCT_HEADER_H_
