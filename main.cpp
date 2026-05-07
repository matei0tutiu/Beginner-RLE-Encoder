#include <iostream>
#include "Buffer.h"
#include "RLEEncoder.h"
#include "FileWriter.h"

#include <fstream>

int main() {

    const Buffer<char> source("aaaabbbbcccdddee");

    Buffer<RLEPair> res(RLEEncoder::CalculateRLEBufferSize(source));

    RLEEncoder::Encode(source, res);

    FileWriter::WriteRLEFile(res, "out.rle");

    return 0;
}