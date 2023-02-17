#if !defined(COMMON_HPP_)
#define COMMON_HPP_

#include "chat_message.hpp"
#include <boost/asio.hpp>
#include <deque>

using boost::asio::ip::tcp;
using msg_queue = std::deque<chat_message>;
#endif // COMMON_HPP_
