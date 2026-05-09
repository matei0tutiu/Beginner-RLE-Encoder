//
// Created by Matei on 5/9/2026.
//

#include "FileHandler.h"

#include <fstream>

// Writing

void FileHandler::WriteRLEFile(const char *filePath, const Buffer<RLEPair> &buffer) {
    assert(buffer.Size() > 0 && "Source Buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    for (size_t i = 0; i < buffer.Size(); ++i) {
        outFile << buffer[i].count << buffer[i].character;
    }

    outFile.close();
}

void FileHandler::WriteTXTFile(const char *filePath, const Buffer<char> &buffer) {
    assert(buffer.Size() > 0 && "Source buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    // ReSharper disable once CppUseAuto
    char* result = new char[buffer.Size() + 1]();

    buffer.ToArray(result, buffer.Size() + 1);

    outFile.write(result, buffer.Size());

    delete[] result;
    outFile.close();
}
