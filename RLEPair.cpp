//
// Created by Matei on 5/7/2026.
//

#include "RLEPair.h"

std::ostream& operator<<(std::ostream& os, const RLEPair& pair){
    return os << "RLEPair<" << static_cast<int>(pair.count) << ',' << static_cast<int>(pair.data) << ">";
}