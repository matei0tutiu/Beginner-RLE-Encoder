//
// Created by Matei on 5/7/2026.
//

#ifndef UNTITLED_RLEPAIR_H
#define UNTITLED_RLEPAIR_H


#include <cstdint>
#include "iostream"

struct RLEPair {
    uint8_t count;
    char character;

    friend std::ostream& operator<<(std::ostream& os, const RLEPair& pair) {
        return os << "RLEPair<" << pair.count << ',' << pair.character << ">";
    }

};


#endif //UNTITLED_RLEPAIR_H
