//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_RLEPAIR_H
#define UNTITLED_RLEPAIR_H


#include <cstddef>
#include <cstdint>
#include <iostream>

struct RLEPair;

std::ostream& operator<<(std::ostream& os, const RLEPair& pair);

struct RLEPair {
    uint8_t count;
    std::byte data;

    friend std::ostream& operator<<(std::ostream& os, const RLEPair& pair);
};


#endif //UNTITLED_RLEPAIR_H
