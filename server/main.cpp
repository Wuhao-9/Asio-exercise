#include "chat_server.hpp"
#include "msg_format.pb.h"
#include <boost/asio.hpp>

#include <iostream>
#include <list>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: Chat-room <port> [<port> ...]" << std::endl;
        return -1;
    }
    
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    try {
        boost::asio::io_service io_service;
        std::list<chat_server> servers;
        for (int i = 1; i < argc; i++) {
            // servers.emplace_back(chat_server(io_service, ::atoi(argv[i]))); !!!!!!!
            servers.emplace_back(io_service, ::atoi(argv[i]));
        }
        for (auto& server : servers) {
            server.start();
        }

        io_service.run();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();
    
    return 0;
}