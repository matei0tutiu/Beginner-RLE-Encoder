cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Buffer.inl
        Buffer.h
        RLEPair.cpp
        RLEPair.h
        RLEEncoder.cpp
        RLEEncoder.h
        RLEDecoder.cpp
        RLEDecoder.h
        FileWriter.cpp
        FileWriter.h
        FileReader.cpp
        FileReader.h
)
