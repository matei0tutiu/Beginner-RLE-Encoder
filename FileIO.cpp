#include "FileIO.h"

#include <fstream>

// Writing

void FileIO::WriteRLEFile(const char *filePath, const Buffer<RLEPair> &buffer) {
    assert(buffer.Size() > 0 && "Source Buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    for (size_t i = 0; i < buffer.Size(); ++i)
        outFile << buffer[i].count << static_cast<char>(buffer[i].data);

    outFile.close();
}


void FileIO::WriteBINFile(const char* filePath, const Buffer<std::byte>& buffer) {
    assert(buffer.Size() > 0 && "Source buffer is empty");

    std::ofstream outFile(filePath, std::ios::binary);

    for (size_t i = 0; i < buffer.Size(); i++)
        outFile << static_cast<char>(buffer[i]);

    outFile.close();
}

// Reading

Buffer<RLEPair> FileIO::ReadRLEFile(const char* filePath) {

    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);

    if (!inFile)
        throw std::runtime_error("Failed to open file");

    const size_t fileSize = inFile.tellg();
    inFile.seekg(0);

    if (fileSize % 2 != 0) {
        inFile.close();
        throw std::runtime_error("Invalid file: odd number of bytes");
    }

    Buffer<RLEPair> buffer(fileSize / 2);

    inFile.read(reinterpret_cast<char*>(&buffer[0]), static_cast<int>(fileSize));

    inFile.close();

    return buffer;
}

Buffer<std::byte> FileIO::ReadBINFile(const char* filePath) {
    std::ifstream inFile(filePath, std::ios::ate | std::ios::binary);

    std::cout << filePath << std::endl;

    if (!inFile)
        throw std::runtime_error("Failed to open file");

    const size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    Buffer<std::byte> buffer(fileSize);
    char* bufferPtr = reinterpret_cast<char*>(&buffer[0]);
    inFile.read(bufferPtr, static_cast<int>(fileSize));

    inFile.close();

    return buffer;

}