#pragma once
#include <stdint.h>

/// @brief Swaps the endianness of a 16 bit value
/// @param value The value to swap
/// @return value with its endianness swapped
uint16_t swap16(uint16_t value);

/// @brief Swaps the endianness of a 32 bit value
/// @param value The value to swap
/// @return value with its endianness swapped
uint32_t swap32(uint32_t value);
