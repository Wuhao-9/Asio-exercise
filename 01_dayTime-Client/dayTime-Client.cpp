// dayTime-Client.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: client <host>" << std::endl;
		return -1;
	}

	boost::asio::io_service io_service;
	boost::system::error_code err;

	tcp::resolver resolver(io_service);
	tcp::resolver::query query(argv[1], "daytime");	// 传入host地址(IPv4/v6, 域名)与port号，创建query对象
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, err); // 解析终端地址
	if (err) {
		std::cerr << "resolve: Fatal error!" << std::endl;
		return -1;
	}

	tcp::socket sock(io_service); // 创建套接字
	boost::asio::connect(sock, endpoint_iterator, err); // 连接终端
	if (err) {
		std::cerr << "Connetion: Fatal error!" << std::endl;
		return -1;
	}

	while (true) {
		std::array<char, 1024> arr;
		size_t len = sock.read_some(boost::asio::buffer(arr), err); // 同步读到arr中
		if (err == boost::asio::error::eof) {
			// connection closed cleanly by peer
			break;
		} else if (err) {
			std::cerr << "Read_some: Fatal error!" << std::endl;
			return -1;
		}
		std::cout.write(arr.data(), len);
	}

	std::cout << std::flush;
	system("pause");
	return 0;
}
