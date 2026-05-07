//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_FILEWRITER_H
#define UNTITLED_FILEWRITER_H
#include "Buffer.h"
#include "RLEPair.h"


class FileWriter {
public:
    FileWriter() = default;

    static void WriteRLEFile(const Buffer<RLEPair>& source, const char* filePath);

    static void WriteTXTFile(const Buffer<char>& source, const char* filePath);

};


#endif //UNTITLED_FILEWRITER_H
