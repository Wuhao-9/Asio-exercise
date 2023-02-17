#if !defined(CHAT_MSG_HPP)
#define CHAT_MSG_HPP
#include "msg_protocol_type.hpp"
#include <array>
#include <cstring>

class chat_message {
private:

    struct header {
        header() = default;
        header(const msg_type type, const unsigned len)
            : body_size(len)
            , type(type) { }

        unsigned body_size = 0;
        msg_type type;
    };

public:
    enum limit {
        MSG_MAX_BODY_LENGTH = 1024,
        MSG_HEADER_LENGTH = sizeof(header),
        NAME_MAX_LENGTH = 32,
    };
    
    chat_message() = default;
    
    auto data() {
        return message_.data();
    }

    auto data() const {
        return message_.data();
    }

    auto body() {
        return message_.data() + MSG_HEADER_LENGTH;
    }

    auto body() const {
        return message_.data() + MSG_HEADER_LENGTH;
    }

    auto get_total_size() const {
        return MSG_HEADER_LENGTH + msg_header_.body_size;
    }

    auto get_body_size() const {
        return msg_header_.body_size;
    }

    auto get_msg_type() const {
        return msg_header_.type;
    }



    bool parse_input_AND_pack(const std::string& user_input);

    /**
     * @brief  检查头部，并将其copy至缓冲区
     */
    bool decoding_received_header(std::size_t size = MSG_HEADER_LENGTH) {
        if (size != MSG_HEADER_LENGTH || msg_header_.body_size > MSG_MAX_BODY_LENGTH)
            return false;
        ::memcpy(&msg_header_, data(), MSG_HEADER_LENGTH);
        return true;
    }

    chat_message(const msg_type type, const std::string& info);

private:
    auto set_body_length(const std::size_t len) {
        if (len <= MSG_MAX_BODY_LENGTH) {
            msg_header_.body_size = len;
            return true;
        }
        return false;
    }

    bool fill_package(const std::string& info, const msg_type type) {
        if ( this->set_body_length(info.size()) ) {
            msg_header_.type = type;
            ::memcpy(this->data(), &msg_header_, chat_message::MSG_HEADER_LENGTH);
            ::memcpy(this->body(), info.data(), get_body_size());
            return true;
        }
        return false;
    }

private:
    std::array<char, MSG_MAX_BODY_LENGTH + MSG_HEADER_LENGTH> message_;
    struct header msg_header_;
};


#endif // CHAT_MSG_HPP

// #ifndef CHAT_MESSAGE_HPP
// #define CHAT_MESSAGE_HPP

// #include <cstdio>
// #include <cstdlib>
// #include <cstring>

// class chat_message
// {
// public:
//   enum { header_length = 4 };
//   enum { max_body_length = 512 };

//   chat_message()
//     : body_length_(0)
//   {
//   }

//   const char* data() const
//   {
//     return data_;
//   }

//   char* data()
//   {
//     return data_;
//   }

//   size_t length() const
//   {
//     return header_length + body_length_;
//   }

//   const char* body() const
//   {
//     return data_ + header_length;
//   }

//   char* body()
//   {
//     return data_ + header_length;
//   }

//   size_t body_length() const
//   {
//     return body_length_;
//   }

//   void body_length(size_t length)
//   {
//     body_length_ = length;
//     if (body_length_ > max_body_length)
//       body_length_ = max_body_length;
//   }

//   bool decode_header()
//   {
//     using namespace std; // For strncat and atoi.
//     char header[header_length + 1] = "";
//     strncat(header, data_, header_length);
//     body_length_ = atoi(header);
//     if (body_length_ > max_body_length)
//     {
//       body_length_ = 0;
//       return false;
//     }
//     return true;
//   }

//   void encode_header()
//   {
//     using namespace std; // For sprintf and memcpy.
//     char header[header_length + 1] = "";
//     sprintf(header, "%4d", body_length_);
//     memcpy(data_, header, header_length);
//   }

// private:
//   char data_[header_length + max_body_length];
//   size_t body_length_;
// };

// #endif // CHAT_MESSAGE_HPP