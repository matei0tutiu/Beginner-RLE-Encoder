//
// Created by Matei on 5/7/2026.
//

#include "RLEDecoder.h"


void RLEDecoder::Decode(const Buffer<RLEPair>& in, Buffer<char>& out) {
    assert(in.Size() != 0 && out.Size() != 0 && "Trying to use null-length buffers");

    size_t currentResultIndex = 0;

    for (int i = 0; i < in.Size(); i++) {
        for (size_t j = 0; j < in[i].count; j++)
            out[currentResultIndex++] = in[i].character;
    }

}

size_t RLEDecoder::CalculateCharBufferSize(const Buffer<RLEPair>& source) {
    if (source.Size() == 0) return 0;

    size_t res = 0;

    for (size_t i = 0; i < source.Size(); i++)
        res += source[i].count;

    return res;

}