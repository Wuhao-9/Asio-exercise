#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <forward_list>
#include <boost\asio.hpp>

std::mutex global_stream_lock;
int xxx;
void WorkerThread(std::shared_ptr<boost::asio::io_service> io_service) {
	global_stream_lock.lock();
	std::cout << "[" << std::this_thread::get_id() << "] Thread start" << std::endl; 
	global_stream_lock.unlock();

	io_service->run();

	global_stream_lock.lock();  
    std::cout << "[" << std::this_thread::get_id()  
        << "] Thread Finish" << std::endl;  
    global_stream_lock.unlock();  
}	

void PrintNum( int x )  
{  
    std::cout << "[" << std::this_thread::get_id()   
        << "] x: " << x << "<" << xxx << ">" << std::endl;   
        xxx++;
}  

int main() {
	std::shared_ptr< boost::asio::io_service > io_service = std::make_shared<boost::asio::io_service>();
	// 让io_service的事件循环阻塞，否则若没有注册的事件，run函数会直接退出
	std::unique_ptr< boost::asio::io_service::work > work =
		std::make_unique< boost::asio::io_service::work >(*io_service); 
	boost::asio::io_service::strand strand( *io_service );
	boost::asio::io_service::strand strand3( *io_service );

    std::cout << "[" <<  std::this_thread::get_id()    
        << "] The program will exit when all  work has finished." <<  std::endl;  

	std::forward_list<std::thread> list;
	for (int x = 0; x < 4; x++) {
		list.push_front(std::thread([io_service]() {
			WorkerThread(std::move(io_service));
		}));
	}



	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	// io_service->post(  strand.wrap([]() {PrintNum(1); }));
	// io_service->post(  strand.wrap([]() {PrintNum(2); }));
    strand.post([]() {PrintNum(1); });
    strand.post([]() {PrintNum(2); });

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	// io_service->post(  strand.wrap([]() {PrintNum(3); }));
	// io_service->post(  strand.wrap([]() {PrintNum(4); }));
    strand.post([]() {PrintNum(3); });
    strand.post([]() {PrintNum(4); });

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	// io_service->post(  strand.wrap([]() {PrintNum(5); }));
	// io_service->post(  strand.wrap([]() {PrintNum(6); }));
    strand.post([]() {PrintNum(5); });
    strand.post([]() {PrintNum(6); });

	// 释放掉 boost::asio::io_service::work 对象，否则io_service会一直阻塞在run函数中
	work.reset();

	for (auto& each_thread : list) {
		each_thread.join();
	}
	
	return 0;
}


/**
 * Conclusion:
 * A: 有序的俩要素：（strand， strand.post）
 *      strand.post( boost::bind( &PrintNum, 1 ) );  
 *      strand.post( boost::bind( &PrintNum, 2 ) );  
 *      strand.post( boost::bind( &PrintNum, 3 ) );  
 *  
 * B: 该情况只保证非并发，不保证顺序
 *      io_service->post( strand.wrap( boost::bind( &PrintNum, 1) ) );  
 *      io_service->post( strand.wrap( boost::bind( &PrintNum, 2 ) ) );  
 *      io_service->post( strand.wrap( boost::bind( &PrintNum, 3 ) ) );  
 */