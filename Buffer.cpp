//
// Created by Matei on 5/10/2026.
//

// Specialization

#include "Buffer.h"


Buffer<char>::Buffer(const char* string)  : BufferBase(std::strlen(string)) {
    for (size_t i = 0; i < _size; i++)
        _data[i] = string[i];
}

void Buffer<char>::ToArray(char* out, const size_t outSize) const {
    assert(_size + 1 == outSize && "Array size mismatch");

    for (size_t i = 0; i < _size; i++)
        out[i] = _data[i];

    out[_size] = '\0';
}

std::ostream& operator<<(std::ostream& os, const Buffer<char>& buffer) {

    for (size_t i = 0; i < buffer.Size();i++)
        os << buffer._data[i];

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::byte byte){
    constexpr char lookup[] = "0123456789abcdef";

    os << lookup[static_cast<int>(byte) >> 4] << lookup[static_cast<int>(byte) & 0xf];

    return os;
}

std::ostream& operator<<(std::ostream& os, const Buffer<std::byte>& buffer) {
    for (size_t i = 0; i < buffer.Size(); i++) {
        os << buffer[i] << ' ';

        if (i % 8 == 7)
            os << '\n';
    }

    return os;
}
