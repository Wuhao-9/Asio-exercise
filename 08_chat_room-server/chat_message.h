#if !defined(CHAT_MESSAGE_H_)
#define CHAT_MESSAGE_H_

#include <array>
#include <deque>
#include <string>
#include <algorithm>
#include <iostream>


class chat_message;

using chat_msg_queue = std::deque<chat_message>;

class chat_message {
public:
    enum limit {
        Header_len = 4,
        Max_body_len = 512
    };

    chat_message()
        : _body_len(0) 
        , _msg() { }

    const char* data() const { return _msg.data(); }

    char* data() { return _msg.data(); }

    ::size_t total_length() const { return limit::Header_len + _body_len; }

    const char* body() const { return data() + limit::Header_len; }

    char* body() { return data() + limit::Header_len; }

    ::size_t get_body_len() const { return _body_len; }

    void set_body_len(::size_t len) {
        len > limit::Max_body_len ? _body_len = limit::Max_body_len : _body_len = len;
    }

    bool decode_header() {
        char tmp_header[limit::Header_len + 1] = {};
        std::strncat(tmp_header, _msg.data(), limit::Header_len);
        auto cur_len = ::atoi(tmp_header);
        if (cur_len > limit::Max_body_len) {
            _body_len = 0;
            return false;
        } else {
            _body_len = cur_len;
            return true;
        }
    }

    void encode_header() {
        char tmp_header[limit::Header_len + 1] = {};
        ::sprintf_s(tmp_header, "%4d", static_cast<int>(_body_len));
        ::memcpy(data(), tmp_header, limit::Header_len);
    }

private:
    std::array<char, limit::Header_len + limit::Max_body_len + 1> _msg;
    ::size_t _body_len;
};


#endif // CHAT_MESSAGE_H_