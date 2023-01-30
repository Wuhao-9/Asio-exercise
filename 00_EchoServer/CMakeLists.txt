# CMakeList.txt: EchoServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


project ("EchoServer")
# Specify MSVC UTF-8 encoding   

set(CMAKE_BUILD_TYPE "Release")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(C:/MyTools/Boost/boost_1_79_0)

# 将源代码添加到此项目的可执行文件。
add_executable (EchoServer "EchoServer.cpp" "EchoServer.h")

# TODO: 如有需要，请添加测试并安装目标。
