//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_FILEREADER_H
#define UNTITLED_FILEREADER_H
#include "Buffer.h"
#include "RLEPair.h"


class FileReader {
public:
    FileReader() = delete;

    void ReadTXTFile(const char* filePath, Buffer<char>& buffer);

    void ReadRLEFile(const char* filePath, Buffer<RLEPair>& buffer);

};


#endif //UNTITLED_FILEREADER_H
