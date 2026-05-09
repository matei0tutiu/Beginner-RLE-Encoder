#include "Buffer.h"
#include "RLEHandler.h"
#include "FileHandler.h"



int main() {

    const Buffer<char> textBuffer("aaaaaaaaaabbbbbbbbbbbbbeeeeeeeeeeeedddddddddddddd");

    Buffer<RLEPair> encodedBuffer(RLEHandler::GetEncodedSize(textBuffer));

    RLEHandler::Encode(textBuffer, encodedBuffer);

    FileHandler::WriteTXTFile("out.txt", textBuffer);
    FileHandler::WriteRLEFile("out.rle", encodedBuffer);


    return 0;
}