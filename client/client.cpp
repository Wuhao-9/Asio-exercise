#include "common.hpp"
#include "chat_client.hpp"
#include "chat_message.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include <thread>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: Chat-client <host> <port>" << std::endl;
        return -1;
    }

    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::endpoint server_endpoint = (*endpoint_iterator).endpoint();

        chat_client instance_of_client(io_service, endpoint_iterator);
        instance_of_client.start();
        
        std::thread t([&io_service]() { 
            try {
                io_service.run();
            } catch (std::exception& e) {
                std::cerr << __LINE__ << e.what() << '\n';
            }
        });

        std::array<char, chat_message::limit::MSG_MAX_BODY_LENGTH + 1> line;
        while (std::cin.getline(line.data(), chat_message::limit::MSG_MAX_BODY_LENGTH + 1)) {
            std::string input(line.data(), line.data() + std::strlen(line.data()));
            chat_message package;
            if (package.parse_input_AND_pack(input)) {
                instance_of_client.send_to_serve(package);
            } else {
                std::cerr << "Request failure!" << std::endl;
            }
        }

        
        t.join();

    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}