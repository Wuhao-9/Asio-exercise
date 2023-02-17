cmake_minimum_required(VERSION 3.0)

project(chat-room VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set(UTILS_DIR_PATH ${CMAKE_SOURCE_DIR}/utils)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(BOOST_PATH "usr/include")
set(PROTOBUF_PATH "/home/wuhao/myTools/protobuf-3.21.12/src/")
set(CXX_STANDARD_REQUIRED c++14)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D PROTOBUF_USE_DLLS")

include_directories(${BOOST_PATH})
include_directories(${UTILS_DIR_PATH})
include_directories(${PROTOBUF_PATH})

set(PROTO_GENERATED ON)
if(NOT PROTO_GENERATED)
    execute_process(COMMAND "protoc" -I${CMAKE_SOURCE_DIR}/utils msg_format.proto --cpp_out=/home/wuhao/myProj/Chat-room/utils)
endif(NOT PROTO_GENERATED)


# file(GLOB SRCS "${CMAKE_SOURCE_DIR}/srcs/*.cpp ${CMAKE_SOURCE_DIR}/utils/*.cpp ${CMAKE_SOURCE_DIR}/utils/*.cc")

link_directories("/home/wuhao/myTools/protobuf-3.21.12/cmake/build") # protobuf`s dependents

link_libraries(pthread boost_thread protobuf)

add_subdirectory(${CMAKE_SOURCE_DIR}/server)
add_subdirectory(${CMAKE_SOURCE_DIR}/client)
