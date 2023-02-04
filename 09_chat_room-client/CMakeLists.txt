cmake_minimum_required(VERSION 3.0)

project(Chat-client)

include_directories(C:/MyTools/Boost/boost_1_79_0)
include_directories(C:/MyTools/protobuf-3.21.12/src)
include_directories(../08_chat_room-server)

add_definitions("-w")

link_directories(C:/MyTools/protobuf-3.21.12/cmake/build/Debug)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME} client.cpp C:/MyProjects/VS_Proj/08_chat_room-server/msg_protocol.pb.cc
C:/MyProjects/VS_Proj/08_chat_room-server/struct_header.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} libprotobufd)