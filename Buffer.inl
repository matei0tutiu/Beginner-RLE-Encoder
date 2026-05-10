//
// Created by Matei on 5/7/2026.
//

// ReSharper disable once CppMissingIncludeGuard
#include <cassert>
#include <cstring>

// --------------- Constructor and Deconstructor

template <typename T>
BufferBase<T>::BufferBase(const size_t size) : _data(new T[size]()), _size(size){}

template <typename T>
BufferBase<T>::~BufferBase() { delete[] _data;}


// ---------------- Copying
template <typename T>
BufferBase<T>::BufferBase(const BufferBase& other) {
    _size = other._size;
    _data = new T[_size];

    for (size_t i = 0; i < _size; i++)
        _data[i] = other._data[i];
}

template <typename T>
void BufferBase<T>::CopyFrom(const BufferBase& other) {
    if (_size != other._size) {
        delete[] _data;
        _size = other._size;
        _data = new T[_size]();
    }

    for (size_t i = 0; i < _size; i++)
        _data[i] = other._data[i];
}

// ------------------ Moving

template <typename T>
BufferBase<T>::BufferBase(BufferBase&& other) noexcept {
    _size = other._size;
    _data = other._data;

    other._size = 0;
    other._data = nullptr;
}

template <typename T>
BufferBase<T>& BufferBase<T>::operator=(BufferBase&& other) noexcept {
    if (this == &other)
            return *this;

    delete[] _data;
    _size = other._size;
    _data = other._data;

    other._size = 0;
    other._data = nullptr;

    return *this;
}

// ----------- Accessing

template <typename T>
T& BufferBase<T>::operator[](const size_t index) {
    assert(index < _size && "Trying to access buffer outside the bounds");

    return _data[index];
}

template <typename T>
const T& BufferBase<T>::operator[](const size_t index) const {
    assert(index < _size && "Trying to access buffer outside the bounds");

    return _data[index];
}

// Public getters
template <typename T>
size_t BufferBase<T>::Size() const {return _size;}

// Equality operator
template <typename T>
bool BufferBase<T>::operator==(const BufferBase& other) const {return _data == other._data; }

// Printing
template <typename T>
std::ostream& operator<<(std::ostream& os, const BufferBase<T>& buffer)    {
    os << "Buffer<";

    if (buffer._size != 0)
        for (size_t i = 0; i < buffer._size; i++)
            os << buffer._data[i] << ' ';

    os << ">[size=" << buffer._size << ']';

    return os;
}

template <typename T>
Buffer<T> BufferBase<T>::Range(const size_t start, const size_t end) const {
    assert(start < end && "The end index must be strictly greater then the start index");
    assert(end <= this->_size && "Cannot copy outside the buffer");

    Buffer<T> result(end - start);

    for (size_t i = 0; i < result.Size(); i++)
        result[i] = this->_data[start + i];

    return result;
}

