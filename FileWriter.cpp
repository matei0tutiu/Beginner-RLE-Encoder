//
// Created by Matei on 5/7/2026.
//

#include "FileWriter.h"

#include <fstream>

void FileWriter::WriteTXTFile(const Buffer<char>& source, const char* filePath) {
    assert(source.Size() > 0 && "Source buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    char* result = new char[source.Size() + 1];

    source.ToArray(result);

    outFile.write(result, source.Size() + 1);

    delete[] result;
    outFile.close();
}

void FileWriter::WriteRLEFile(const Buffer<RLEPair>& source, const char* filePath) {
    assert(source.Size() > 0 && "Source Buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    for (size_t i = 0; i < source.Size(); ++i) {
        outFile << source[i].count << source[i].character;
    }

    outFile.close();
}
