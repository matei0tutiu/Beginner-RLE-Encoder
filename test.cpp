#include <filesystem>
#include "Utils.h"
#include "Operations.h"
#include "FileIO.h"

const std::filesystem::path originalsDirectory("./test_files/original_files/");
const std::filesystem::path encodedDirectory("./test_files/encoded_files/");
const std::filesystem::path decodedDirectory("./test_files/decoded_files/");

struct FileTracker {
    std::filesystem::path originalPath;
    std::filesystem::path encodedPath;
    std::filesystem::path decodedPath;

    explicit FileTracker(const char* file){
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

        Buffer<std::byte> source = FileIO::ReadBINFile(file.originalPath.string().c_str());
        Buffer<std::byte> decoded = FileIO::ReadBINFile(file.decodedPath.string().c_str());

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
                std::cout << COLOR_GREEN << Truncate(test.relativeSize) * 100;
            else
                std::cout << COLOR_RED << Truncate(test.relativeSize) * 100;

            std::cout << "% " << '\n';

            std::cout << COLOR_WHITE << "Relative delta: ";
            if (test.relativeSize < 1)
                std::cout << COLOR_GREEN << Truncate(1 - test.relativeSize) * 100  << "% reduction in size" << '\n';
            else
                std::cout << COLOR_RED << Truncate(test.relativeSize - 1) * 100  << "% increase in size" << '\n';

        }else
            std::cout << COLOR_RED << "RUN TEST TO SEE RESULTS!\n";

        std::cout << COLOR_PURPLE << "\n============================================================================================\n" << COLOR_RESET;
        return os;
    }

};

Test tests[] = {
    Test("tree.bmp"),
    Test( "strips_horizontal.bmp"),
    Test("strips_vertical_8b.bmp"),
    Test("strips_vertical_24b.bmp"),
    Test("wave.bmp"),
    Test("night.bmp"),
    Test("code.txt"),
};
constexpr size_t testCount = sizeof(tests) / sizeof(Test);

int main() {

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