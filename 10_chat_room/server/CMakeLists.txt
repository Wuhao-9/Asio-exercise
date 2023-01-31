cmake_minimum_required(VERSION 3.0)

project(Chat_room-Server)

include_directories(C:/MyTools/Boost/boost_1_79_0)

include_directories(C:/MyProjects/VS_Proj/10_chat_room/server/include)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME} main.cpp)