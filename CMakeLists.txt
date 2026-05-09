cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Buffer.inl
        Buffer.h
        RLEPair.cpp
        RLEPair.h
        FileHandler.cpp
        FileHandler.h
        RLEHandler.cpp
        RLEHandler.h
)
