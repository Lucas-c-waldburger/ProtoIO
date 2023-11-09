cmake_minimum_required(VERSION 3.24)
project(ProtoIO)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_PROTOBUF "Run the protobuf cmake from dependencies folder" OFF)

if (BUILD_PROTOBUF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/protobuf _protobuf)
endif(BUILD_PROTOBUF)

find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        ProtoIO
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

target_link_libraries(ProtoIO ${Protobuf_LIBRARIES})

set_target_properties(ProtoIO PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")