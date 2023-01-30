#include <ctime>

#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
	::time_t now = time(nullptr); // time: 获取当前时间戳
	return ::ctime(&now); // ctime： 将当前时间表示为const char*返回 (多线程下不安全，内部const char*为static)
}

int main() {
	try {
		boost::asio::io_service io_service;

		// 创建acceptor，并且绑定地址和端口
		// 服务器端只接受IPv4地址的客户端
		tcp::acceptor accepter(io_service, tcp::endpoint(tcp::v4(), 13));
		std::cout << "The Server is start..." << std::endl;

		while (true) {
			tcp::socket socket(io_service);
			accepter.accept(socket); // 同步等待客户端连接

			std::string msg = make_daytime_string();

			boost::system::error_code ignored_error; // 避免异常，防止单个客户端影响整个服务器退出
			boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
			if (ignored_error) {
				std::cout << ignored_error.what() << std::endl;
			}
			socket.close();
		}

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Bye" << std::endl;
	system("pause");
	return 0;
}