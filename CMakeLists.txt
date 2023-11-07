cmake_minimum_required(VERSION 3.24)
project(protobufTest2)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        protobufTest2
        main.cpp
        src/ProtoIO.cpp
        include/ProtoIO.h
        src/Utils.cpp
        include/Utils.h
        include/defs.h
        dependencies/CardData.pb.h
        dependencies/CardData.pb.cc
        ${PROTO_SRCS} ${PROTO_HDRS}
)

target_link_libraries(protobufTest2 ${Protobuf_LIBRARIES})