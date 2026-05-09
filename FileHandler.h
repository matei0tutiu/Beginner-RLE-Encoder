//
// Created by Matei on 5/9/2026.
//

#ifndef UNTITLED_FILEHANDLER_H
#define UNTITLED_FILEHANDLER_H

#include "Buffer.h"
#include "RLEPair.h"

class FileHandler {

public:
    FileHandler() = delete;


    static void ReadTXTFile(const char* filePath, Buffer<char>& buffer);
    static void ReadRLEFile(const char* filePath, Buffer<RLEPair>& buffer);


    static void WriteTXTFile(const char* filePath, const Buffer<char>& buffer);
    static void WriteRLEFile(const char* filePath, const Buffer<RLEPair>& buffer);
};


#endif //UNTITLED_FILEHANDLER_H
