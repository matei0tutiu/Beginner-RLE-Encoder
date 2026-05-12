//
// Created by Matei on 5/12/2026.
//

#include "Utils.h"
#include "RLE.h"

[[nodiscard]] float CalculateRelativeSize(const Buffer<std::byte>& raw) {
    const size_t encodedSize = RLE::GetEncodedSize(raw);
    const float f = 2 * static_cast<float>(encodedSize) / static_cast<float>(raw.Size());
    return f;
}

[[nodiscard]] float Truncate(const float f) {
    return static_cast<float>(static_cast<int>(f * 100 * 100)) / (100 * 100);
}

[[nodiscard]]  bool checkOptionValidity(const char* option) {
    return strlen(option) == 2 && option[0] == '-' && (option[1] == 'd' || option[1] == 'D' || option[1] == 'e' || option[1] == 'E');
}