//
// Created by Matei on 5/7/2026.
//

#include "RLEEncoder.h"
#include <cassert>

void RLEEncoder::Encode(const Buffer<char>& in, Buffer<RLEPair>& out) {
    assert(in.Size() != 0 && out.Size() != 0 && "Trying to use null-length buffers");

    out[0].character = in[0];
    out[0].count = 1;
    size_t currentResultIndex = 0;

    for (size_t i = 1; i < in.Size(); i++)
        if (out[currentResultIndex].character != in[i] || out[currentResultIndex].count >= 253) {
            // we need to start a new run
            currentResultIndex++;
            out[currentResultIndex].character = in[i];
            out[currentResultIndex].count++;

        }else {
            out[currentResultIndex].count++;
        }


}

size_t RLEEncoder::CalculateRLEBufferSize(const Buffer<char> &charBuffer) {
    if (charBuffer.Size() == 0) return 0;

    size_t currentRunStartIndex = 0, requiredSize = 1;
    char currentRunChar = charBuffer[currentRunStartIndex];

    for (size_t i = 1; i < charBuffer.Size(); i++)
        if (currentRunChar != charBuffer[i] || i - currentRunStartIndex > 250) {
            // run ended, we start a new one, and that requires another slot in the output buffer
            requiredSize++;

            currentRunStartIndex = i;
            currentRunChar = charBuffer[i];
        }


    return requiredSize;
}
