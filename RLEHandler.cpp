//
// Created by Matei on 5/9/2026.
//

#include "RLEHandler.h"
#include <cassert>

#define MAX_RUN_COUNT 254

size_t RLEHandler::GetEncodedSize(const Buffer<std::byte>& source) {
    if (source.Size() == 0) return 0;

    // check one-by-one for runs and add up the numbers of runs

    RLEPair currentRun = {1, source[0]};
    size_t result = 1;

    for (size_t i = 1; i < source.Size();i++)
        if (source[i] != currentRun.data || currentRun.count >= MAX_RUN_COUNT) {
            result++;

            currentRun.count = 1;
            currentRun.data = source[i];
        }else
            currentRun.count++;

    return result;
}

void RLEHandler::Encode(const Buffer<std::byte>& source, Buffer<RLEPair>& destination) {
    assert(source.Size() != 0 && "Error: Trying to encode a null-length buffer");
    assert(destination.Size() == GetEncodedSize(source) && "Error: Destination buffer is not the proper size for encoding");

    size_t destinationIndex = 0;
    destination[0] = {1, source[0]};

    for (size_t i = 1; i < source.Size(); i++)
        // check if the current character matches with the run and if the count didn't overflow
        if (source[i] != destination[destinationIndex].data || destination[destinationIndex].count >= MAX_RUN_COUNT)  {
            // we need save the current run and start a new one
            destinationIndex++;

            destination[destinationIndex] = {1, source[i]};
        }else // we increase the counter of the current run
            destination[destinationIndex].count++;
}

Buffer<RLEPair> RLEHandler::Encode(const Buffer<std::byte>& source) {

    Buffer<RLEPair> result(GetEncodedSize(source));
    Encode(source, result);
    return result;
}

size_t RLEHandler::GetDecodedSize(const Buffer<RLEPair>& source) {
    if (source.Size() == 0) return 0;

    // loop over all the pairs and add up the counts
    size_t result = 0;

    for (size_t i = 0; i < source.Size(); i++)
            result += source[i].count;

    return result;
}

void RLEHandler::Decode(const Buffer<RLEPair>& source, Buffer<std::byte>& destination) {
    assert(source.Size() != 0 && "Error: Trying to decode a null-length buffer");
    assert(destination.Size() == GetDecodedSize(source) && "Error: Destination buffer is not the proper size for decoding");

    size_t destinationIndex = 0;

    for (int i = 0; i < source.Size(); i++)
        for (int j = 0; j < source[i].count; j++)
            destination[destinationIndex++] = source[i].data;
}

Buffer<std::byte> RLEHandler::Decode(const Buffer<RLEPair>& source) {
    Buffer<std::byte> result(GetDecodedSize(source));
    Decode(source, result);
    return result;
}