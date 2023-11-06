cmake_minimum_required(VERSION 3.24)
project(protobufTest2)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)


add_executable(protobufTest2 main.cpp src/ProtoIO.cpp include/ProtoIO.h src/Utils.cpp include/Utils.h CardDataSrcMap.cpp CardDataSrcMap.h CDAliases.cpp CDAliases.h CDWrappers.cpp CDWrappers.h include/defs.h include/defs.h)
