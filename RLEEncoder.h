//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_RLEENCODER_H
#define UNTITLED_RLEENCODER_H

#include "Buffer.h"
#include "RLEPair.h"

class RLEEncoder {
public:
    RLEEncoder() = delete;

    static void Encode(const Buffer<char>& in, Buffer<RLEPair>& out);

    static size_t CalculateRLEBufferSize(const Buffer<char>& charBuffer);

};


#endif //UNTITLED_RLEENCODER_H
