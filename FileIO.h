//
// Created by Matei on 5/9/2026.
//

#ifndef UNTITLED_FILEHANDLER_H
#define UNTITLED_FILEHANDLER_H

#include "Buffer.h"
#include "RLEPair.h"


class FileIO {

public:
    FileIO() = delete;

    ///@brief Used to read a `.rle` file
    ///@exception Incorrect_File If the file is not correct ( it does not have an even number of bytes ) it throws a `runtime_error`
    static Buffer<RLEPair> ReadRLEFile(const char* filePath);
    ///@brief Used to interpret any kind of file as raw binary data
    static Buffer<std::byte> ReadBINFile(const char* filePath);

    ///@brief Writes RLE data to a file
    static void WriteRLEFile(const char* filePath, const Buffer<RLEPair>& buffer);
    ///@brief Writes files as raw binary data
    static void WriteBINFile(const char* filePath, const Buffer<std::byte>& buffer);
};


#endif //UNTITLED_FILEHANDLER_H
