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
    size_t Size() const;
    bool IsAllocated() const;

    // Equality Operator
    bool operator==(const BufferBase& other) const;

    // Streaming operator

    friend std::ostream& operator<<(std::ostream& os, const BufferBase& buffer)
    {
        os << "Buffer<";

        if (buffer._size != 0)
            for (size_t i = 0; i < buffer._size; i++)
                os << buffer._data[i] << ' ';

        os << ">[size=" << buffer._size << ']';

        return os;
    }

protected:
    T* _data;
    size_t _size;

};

template <typename T>
class Buffer : public BufferBase<T> {
    using BufferBase<T>::BufferBase;
};

template <>
class Buffer<char> : public BufferBase<char> {
    using BufferBase<char>::BufferBase;
public:
    explicit Buffer(const char* string);

    void ToArray(char* out) const;

};

#include "Buffer.inl"

#endif //UNTITLED_BUFFER_H
