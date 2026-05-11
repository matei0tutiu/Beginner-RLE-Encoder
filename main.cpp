#include "Buffer.h"
#include "RLEHandler.h"
#include "FileHandler.h"

#include <filesystem>

#define SOURCE_PATH_ARGV_INDEX 1
#define OUTPUT_PATH_ARGV_INDEX 2
#define MODE_ARGV_INDEX 3

#define COLOR_WHITE "\e[0;37m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GREEN "\e[0;32m"
#define COLOR_ORANGE "\e[0;34m"
#define COLOR_PURPLE "\e[0;35m"
#define COLOR_RESET "\e[0m"


[[nodiscard]]float CalculateRelativeSize(const Buffer<std::byte>& raw) {
    const size_t encodedSize = RLEHandler::GetEncodedSize(raw);
    const float f = 2 * static_cast<float>(encodedSize) / static_cast<float>(raw.Size());
    return f;
}

[[nodiscard]]float Approximated(const float f) {
    return static_cast<float>(static_cast<int>(f * 100 * 100)) / (100 * 100);
}


bool checkOptionValidity(const char* option) {

    return strlen(option) == 2 && option[0] == '-' && (option[1] == 'd' || option[1] == 'D' || option[1] == 'e' || option[1] == 'E');
}

float Encode(const std::filesystem::path& sourcePath, const std::filesystem::path& outputPath) {
    if (sourcePath.empty())
        throw std::runtime_error("Source path is empty");

    if (outputPath.extension() != ".rle")
        throw std::runtime_error("Invalid output file format");

    const Buffer<std::byte> raw = FileHandler::ReadBINFile(sourcePath.string().c_str());
    const Buffer<RLEPair> encoded = RLEHandler::Encode(raw);

    std::filesystem::create_directories(outputPath.parent_path());
    FileHandler::WriteRLEFile(outputPath.string().c_str(), encoded);

    const float relativeSize = CalculateRelativeSize(raw);

    std::cout << COLOR_PURPLE << "Profile for { " << COLOR_ORANGE << sourcePath.string() << " }" << COLOR_RESET << '\n';

    std::cout << raw.Size() << " bytes [raw] -> " << 2 * encoded.Size() << " (" << 100 * relativeSize << "% * size of raw data) [encoded] | ";
    if (relativeSize <= 1)
        std::cout << COLOR_GREEN << Approximated(1-relativeSize) * 100 << "% reduction in size" << COLOR_RESET<< std::endl;
    else
        std::cout << COLOR_RED << Approximated(relativeSize - 1) * 100 << "% increase in size" << COLOR_RESET << std::endl;

    std::cout << COLOR_PURPLE << "\n-------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;

    return relativeSize;
}

void Decode(const std::filesystem::path& sourcePath, const std::filesystem::path& outputPath) {
    // decode mode

    if (sourcePath.extension() != ".rle")
        throw std::runtime_error("Invalid input file format");

    if (outputPath.empty())
        throw std::runtime_error("Output path is empty");

    const Buffer<RLEPair> encoded = FileHandler::ReadRLEFile(sourcePath.string().c_str());
    const Buffer<std::byte> decoded = RLEHandler::Decode(encoded);

    std::filesystem::create_directories(outputPath.parent_path());
    FileHandler::WriteBINFile(outputPath.string().c_str(), decoded);

    std::cout << COLOR_PURPLE << "Profile for { " << COLOR_ORANGE << sourcePath.string() << COLOR_PURPLE << " }\n" << COLOR_RESET;
    std::cout << COLOR_GREEN << " Decoding successful !" << COLOR_RESET<< std::endl;
    std::cout << COLOR_PURPLE << "\n-------------------------------------------------------------------------------------------------------\n" << COLOR_RESET;
}

void runProject(const int argc, const char** argv) {
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
}


const std::filesystem::path originalsDirectory("./test_files/original_files/");
const std::filesystem::path encodedDirectory("./test_files/encoded_files/");
const std::filesystem::path decodedDirectory("./test_files/decoded_files/");

struct FileTracker {
    std::filesystem::path originalPath;
    std::filesystem::path encodedPath;
    std::filesystem::path decodedPath;

    FileTracker(const char* file){
        originalPath = originalsDirectory.string() + std::string(file);
        encodedPath = encodedDirectory.string() + std::string(file);
        encodedPath.replace_extension(".rle");
        decodedPath = decodedDirectory.string() + std::string(file);
    }
};

struct Test {
    const std::string fileName;
    const FileTracker file;
    float relativeSize;
    bool completed, success;

    explicit Test(const char* FileName) : fileName(FileName), file(FileName), relativeSize(0), completed(false), success(true) {}

    bool Run() {
        if (completed)
            throw std::runtime_error("Test already completed");

        std::cout << "File paths: (original, encoded, decoded): " << file.originalPath.string() << ',' << file.encodedPath.string() << ',' << file.decodedPath.string() << std::endl;

        relativeSize = Encode(file.originalPath, file.encodedPath);
        Decode(file.encodedPath, file.decodedPath);

        Buffer<std::byte> source = FileHandler::ReadBINFile(file.originalPath.string().c_str());
        Buffer<std::byte> decoded = FileHandler::ReadBINFile(file.decodedPath.string().c_str());

        if (source.Size() != decoded.Size()) {
            success = false;
            completed = true;
            return success;
        }

        for (size_t i = 0; i < source.Size(); i++)
            if (source[i] != decoded[i])
                success = false;

        completed = true;
        return success;
    }

    friend std::ostream& operator<<(std::ostream& os, const Test& test) {

        std::cout << COLOR_PURPLE << "========================== Profile for { " << COLOR_ORANGE << test.fileName <<  COLOR_PURPLE << " }" << " =======================================\n\n";

        if (test.completed) {
            std::cout << COLOR_WHITE <<  "Original path: " << COLOR_ORANGE << test.file.originalPath.string() << '\n';
            std::cout << COLOR_WHITE << "Encoded path: " << COLOR_ORANGE  << test.file.encodedPath.string() << '\n';
            std::cout << COLOR_WHITE << "Decoded path: " << COLOR_ORANGE << test.file.decodedPath.string() << "\n\n";

            std::cout << COLOR_WHITE << "Status: ";
            if (test.success)
                std::cout << COLOR_GREEN << "SUCCESS" << '\n';
            else
                std::cout << COLOR_RED << "FAILED" << '\n';

            std::cout << COLOR_WHITE << "Relative size: ";
            if (test.relativeSize <= 1)
                std::cout << COLOR_GREEN << Approximated(test.relativeSize) * 100;
            else
                std::cout << COLOR_RED << Approximated(test.relativeSize) * 100;

            std::cout << "% " << '\n';

            std::cout << COLOR_WHITE << "Relative delta: ";
            if (test.relativeSize < 1)
                std::cout << COLOR_GREEN << Approximated(1 - test.relativeSize) * 100  << "% reduction in size" << '\n';
            else
                std::cout << COLOR_RED << Approximated(test.relativeSize - 1) * 100  << "% increase in size" << '\n';

        }else
            std::cout << COLOR_RED << "RUN TEST TO SEE RESULTS!\n";

        std::cout << COLOR_PURPLE << "\n============================================================================================\n" << COLOR_RESET;
        return os;
    }

};

Test tests[] = {
    Test("white.bmp"),
    Test("the_great_wave_off_kanagawa.bmp"),
    Test("stairy_night.bmp"),
    Test("Liberty_Leading_People.bmp"),
    Test("file.bin"),
    Test("all_colors_vertical.bmp"),
    Test( "all_colors_horizontal.bmp"),
};
constexpr size_t testCount = sizeof(tests) / sizeof(Test);

int main(const int argc, const char** argv) {

    for (auto &test : tests)
        test.Run();

    std::cout << COLOR_RED << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TEST PROFILES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << COLOR_RESET << std::endl;

    for (auto &test : tests)
        std::cout << test;

    std::filesystem::remove_all(encodedDirectory);
    std::filesystem::remove_all(decodedDirectory);

    std::filesystem::create_directory(encodedDirectory);
    std::filesystem::create_directory(decodedDirectory);

    return 0;
}