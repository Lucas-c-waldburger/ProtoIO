cmake_minimum_required(VERSION 3.24)
project(protobufTest2)

set(CMAKE_CXX_STANDARD 17)

add_executable(protobufTest2 main.cpp ProtoIO.cpp ProtoIO.h CDMake.cpp CDMake.h)
