#include <cstring>
#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum class Max_len { Len = 5 };

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "usage: Echo-client <host> <port>" << std::endl;
        return -1;
    }

    try {
        boost::system::error_code err;
        boost::asio::io_service io_service;
        tcp::socket local_sock(io_service);
        tcp::resolver reslover(io_service);
        boost::asio::connect(
            local_sock, 
            // reslover.resolve({argv[1], argv[2]})  // 等价于下一行
            reslover.resolve(tcp::resolver::query(argv[1], argv[2]))
        );
 
        while (true) {
            char request_buffer[static_cast<unsigned long long>(Max_len::Len)] {}; // init request_buffer
            std::cout << "Enter message: ";
            std::cin.getline(request_buffer, static_cast<unsigned long long>(Max_len::Len)); // 接收要输入的数据
            if (std::cin.fail()) { 
                std::cin.clear();
            } // 判断缓冲区是否溢出
            ::size_t request_len = std::strlen(request_buffer); // 获取要输入的数据的Byte size
            boost::asio::write(local_sock, boost::asio::buffer(request_buffer, request_len)); // 发送数据[同步]

            char reply_buffer[static_cast<unsigned long long>(Max_len::Len)] {}; // init reply_buffer
            ::size_t reply_len = boost::asio::read(
                local_sock,
                boost::asio::buffer(reply_buffer, request_len) // 只接收发送的字节大小    
            );
            
            std::cout << "Reply is: "; 
            std::cout << reply_buffer;
            std::cout << std::endl; 
        }

    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}