#pragma once
#include <stdint.h>

//Swaps endian for 16 | 32 | 64 bit values
#define ENDIAN_SWAP(x) _Generic((x),			\
						uint16_t: endianSwap16,	\
						uint32_t: endianSwap32,	\
						uint64_t: endianSwap64	\
					)(x)

/// @brief Swaps the endianness of a 16 bit value
/// @param value The value to swap
/// @return value with its endianness swapped
uint16_t endianSwap16(uint16_t value);

/// @brief Swaps the endianness of a 32 bit value
/// @param value The value to swap
/// @return value with its endianness swapped
uint32_t endianSwap32(uint32_t value);

/// @brief Swaps the endianness of a 64 bit value
/// @param value The value to swap
/// @return value with its endianness swapped
uint64_t endianSwap64(uint64_t value);