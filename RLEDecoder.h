//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_RLEDECODER_H
#define UNTITLED_RLEDECODER_H

#include "Buffer.h"
#include "RLEPair.h"

class RLEDecoder {
public:
    RLEDecoder() = default;

    static void Decode(const Buffer<RLEPair>& in, Buffer<char>& out);

    static size_t CalculateCharBufferSize(const Buffer<RLEPair>& source);
};


#endif //UNTITLED_RLEDECODER_H
