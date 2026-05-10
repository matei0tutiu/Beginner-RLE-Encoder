//
// Created by Matei on 5/9/2026.
//

#ifndef UNTITLED_RLEHANDLER_H
#define UNTITLED_RLEHANDLER_H
#include "Buffer.h"
#include "RLEPair.h"


class RLEHandler {
public:
    RLEHandler() = delete;

    ///@brief Encodes data to a buffer of RLE data
    ///@note The size of destination buffer must match exactly with the output of `GetEncodedSize()`
    static void Encode(const Buffer<std::byte>& source, Buffer<RLEPair>& destination);
    ///@brief Creates a new buffer with the encoded data from `source`
    static Buffer<RLEPair> Encode(const Buffer<std::byte>& source);
    ///@brief Calculates the size of a `Buffer<RLEPair>` required to encode the source buffer
    static size_t GetEncodedSize(const Buffer<std::byte>& source);

    ///@brief Decodes a buffer from RLE data to a buffer of bytes
    ///@note The size of the destination buffer must match exactly with the output of `GetDecodedSize()`
    static void Decode(const Buffer<RLEPair>& source, Buffer<std::byte>& destination);
    ///@brief Creates a new buffer with the decoded data from `source`
    static Buffer<std::byte> Decode(const Buffer<RLEPair>& source);
    ///@brief Calculates the size of a `Buffer<char>` required to decode the source buffer
    static size_t GetDecodedSize(const Buffer<RLEPair>& source);

};


#endif //UNTITLED_RLEHANDLER_H
