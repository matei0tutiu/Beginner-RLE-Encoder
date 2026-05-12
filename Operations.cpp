//
// Created by Matei on 5/12/2026.
//

#include "Operations.h"

#include "Buffer.h"
#include "FileIO.h"
#include "RLE.h"
#include "Utils.h"

float Encode(const std::filesystem::path& sourcePath, const std::filesystem::path& outputPath) {
    if (sourcePath.empty())
        throw std::runtime_error("Source path is empty");

    if (outputPath.extension() != ".rle")
        throw std::runtime_error("Invalid output file format");

    const Buffer<std::byte> raw = FileIO::ReadBINFile(sourcePath.string().c_str());
    const Buffer<RLEPair> encoded = RLE::Encode(raw);

    std::filesystem::create_directories(outputPath.parent_path());
    FileIO::WriteRLEFile(outputPath.string().c_str(), encoded);

    const float relativeSize = CalculateRelativeSize(raw);

    std::cout << COLOR_PURPLE << "Profile for { " << COLOR_ORANGE << sourcePath.string() << " }" << COLOR_RESET << '\n';

    std::cout << raw.Size() << " bytes [raw] -> " << 2 * encoded.Size() << " (" << 100 * relativeSize << "% * size of raw data) [encoded] | ";
    if (relativeSize <= 1)
        std::cout << COLOR_GREEN << Truncate(1-relativeSize) * 100 << "% reduction in size" << COLOR_RESET<< std::endl;
    else
        std::cout << COLOR_RED << Truncate(relativeSize - 1) * 100 << "% increase in size" << COLOR_RESET << std::endl;

    std::cout << COLOR_PURPLE << "\n-------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;

    return relativeSize;
}

void Decode(const std::filesystem::path& sourcePath, const std::filesystem::path& outputPath) {
    // decode mode

    if (sourcePath.extension() != ".rle")
        throw std::runtime_error("Invalid input file format");

    if (outputPath.empty())
        throw std::runtime_error("Output path is empty");

    const Buffer<RLEPair> encoded = FileIO::ReadRLEFile(sourcePath.string().c_str());
    const Buffer<std::byte> decoded = RLE::Decode(encoded);

    std::filesystem::create_directories(outputPath.parent_path());
    FileIO::WriteBINFile(outputPath.string().c_str(), decoded);

    std::cout << COLOR_PURPLE << "Profile for { " << COLOR_ORANGE << sourcePath.string() << COLOR_PURPLE << " }\n" << COLOR_RESET;
    std::cout << COLOR_GREEN << " Decoding successful !" << COLOR_RESET<< std::endl;
    std::cout << COLOR_PURPLE << "\n-------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
}