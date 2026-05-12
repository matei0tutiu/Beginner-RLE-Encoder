#include "Operations.h"
#include "Utils.h"


#include <filesystem>

#define SOURCE_PATH_ARGV_INDEX 1
#define OUTPUT_PATH_ARGV_INDEX 2
#define MODE_ARGV_INDEX 3


int main(const int argc, char** argv) {
    // Make sure there is the correct number of arguments
    if (argc != MODE_ARGV_INDEX + 1)
        throw std::runtime_error("Usage: <inputFilePath> <outputFilePath> <mode>");

    // make sure the mode argument is valid
    if (!checkOptionValidity(argv[MODE_ARGV_INDEX]))
        throw std::runtime_error("Invalid <option> argument");

    const std::filesystem::path sourcePath(argv[SOURCE_PATH_ARGV_INDEX]);
    const std::filesystem::path outputPath(argv[OUTPUT_PATH_ARGV_INDEX]);

    switch (argv[MODE_ARGV_INDEX][1]) {
        case 'e' | 'E':
            Encode(sourcePath, outputPath);
            break;
        case 'd' | 'D':
            Decode(sourcePath, outputPath);
            break;
        default:
            throw std::runtime_error("Invalid mode argument");
    }

    return 0;
}