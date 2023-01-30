cmake_minimum_required(VERSION 3.0)

project(ASYN-timeServer)

include_directories(C:/MyTools/Boost/boost_1_79_0)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)