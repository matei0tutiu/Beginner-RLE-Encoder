//
// Created by Matei on 5/12/2026.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H

#include "Buffer.h"

#define COLOR_WHITE "\e[0;37m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GREEN "\e[0;32m"
#define COLOR_ORANGE "\e[0;34m"
#define COLOR_PURPLE "\e[0;35m"
#define COLOR_RESET "\e[0m"

[[nodiscard]]float CalculateRelativeSize(const Buffer<std::byte>& raw);

[[nodiscard]]float Truncate(float f);

[[nodiscard]]bool checkOptionValidity(const char* option);



#endif //UNTITLED_UTILS_H
