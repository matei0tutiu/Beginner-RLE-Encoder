cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(SHARED_SOURCES
        Buffer.inl
        Buffer.h
        Buffer.cpp
        RLEPair.cpp
        RLEPair.h
        FileIO.cpp
        FileIO.h
        RLE.cpp
        RLE.h
        Operations.cpp
        Operations.h
        Utils.cpp
        Utils.h
)

add_executable(main main.cpp ${SHARED_SOURCES})
add_executable(test test.cpp ${SHARED_SOURCES})
