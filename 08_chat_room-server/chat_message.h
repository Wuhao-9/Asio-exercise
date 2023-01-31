#if !defined(CHAT_MESSAGE_H_)
#define CHAT_MESSAGE_H_

#include "struct_header.h"

#include <array>
#include <deque>
#include <string>
#include <algorithm>
#include <iostream>

#include <cassert>

class chat_message;

using chat_msg_queue = std::deque<chat_message>;

class chat_message {
public:
    enum limit {
        Header_len = sizeof(header),
        Max_body_len = 512
    };

    chat_message()
        : _header() 
        , _msg() { }

    const char* data() const { return _msg.data(); }

    char* data() { return _msg.data(); }

    ::size_t total_length() const { return limit::Header_len + _header.body_size; }

    const char* body() const { return data() + limit::Header_len; }

    char* body() { return data() + limit::Header_len; }

    ::size_t get_body_len() const { return _header.body_size; }

    void set_body_len(::size_t len) {
        len > limit::Max_body_len ? _header.body_size = limit::Max_body_len : _header.body_size = len;
    }

    bool decode_header() {
        ::memcpy(&_header, data(), limit::Header_len);
        if (_header.body_size > limit::Max_body_len) {
            std::cerr << "[error] received error package: " << 
            "The received packet length is greater than the maximum length"
            "[" << _header.body_size << "]";
            _header.body_size = 0;
            return false; 
        }
        return true;
    }

    auto get_msg_type() const { return _header.type; }

    void setMsg_header(const msg_type type, const void* body_data, size_t body_size) {
        assert(body_size <= limit::Max_body_len);
        assert(type >= msg_type::ROOM_INFO || type <= msg_type::CHAT_MSG);
        _header.body_size = body_size;
        _header.type = type;
        ::memcpy(body(), body_data, body_size);
        ::memcpy(data(), &_header, limit::Header_len);
    }

private:
    std::array<char, limit::Header_len + limit::Max_body_len + 1> _msg;
    header _header;
};


#endif // CHAT_MESSAGE_H_