//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_BUFFER_H
#define UNTITLED_BUFFER_H


#include <iostream>

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
    [[nodiscard]] size_t Size() const;

    // Equality Operator
    bool operator==(const BufferBase& other) const;

    // Streaming operator
    friend std::ostream& operator<<(std::ostream& os, const BufferBase& buffer);
protected:
    T* _data;
    size_t _size;

};

// Forward declaration
template <typename T>
std::ostream& operator<<(std::ostream& os, const BufferBase<T>& buffer);

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




#include "Buffer.inl"

#endif //UNTITLED_BUFFER_H
