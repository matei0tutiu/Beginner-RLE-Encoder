//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_BUFFER_H
#define UNTITLED_BUFFER_H

#include "RLEPair.h"
#include <iosfwd>

template <typename T> class Buffer;
template <typename T> class BufferBase;

// Forward declaration
template <typename T>
std::ostream& operator<<(std::ostream& os, const BufferBase<T>& buffer);

template <typename T>
class BufferBase {
public:
    // Constructor
    explicit BufferBase(size_t size);

    // Copying
    BufferBase(const BufferBase& other);
    BufferBase& operator=(const BufferBase& other) = delete;

    void CopyFrom(const BufferBase& other);

    // Moving
    BufferBase(BufferBase&& other) noexcept;
    BufferBase& operator=(BufferBase&& other) noexcept;

    // Deconstructor
    ~BufferBase();

    // Accessor
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Public Getters
    ///@brief Getter for the buffer's size
    [[nodiscard]] size_t Size() const;

    // Equality Operator
    bool operator==(const BufferBase& other) const;

    ///@bried Returns a new buffer containing the range mentioned
    ///@note start is inclusive and end is exclusive
    [[nodiscard]]Buffer<T> Range(size_t start, size_t end) const;

    // Streaming operator
    friend std::ostream& operator<<<T>(std::ostream& os, const BufferBase& buffer);
protected:
    T* _data;
    size_t _size;

};


template <typename T>
class Buffer : public BufferBase<T> {
    using BufferBase<T>::BufferBase;
};

// Specialization
std::ostream& operator<<(std::ostream& os, const Buffer<char>& buffer);

template <>
class Buffer<char> : public BufferBase<char> {
    using BufferBase::BufferBase;
public:
    explicit Buffer(const char* string);

    void ToArray(char* out, size_t outSize) const;

    friend std::ostream& operator<<(std::ostream& os, const Buffer& buffer);
};

std::ostream& operator<<(std::ostream& os, const Buffer<std::byte>& buffer);

template <>
class Buffer<std::byte> : public BufferBase<std::byte> {
    using BufferBase::BufferBase;
public:

    friend std::ostream& operator<<(std::ostream& os, const Buffer& buffer);
};



#include "Buffer.inl"

#endif //UNTITLED_BUFFER_H
