#include "endian.h"

uint16_t endianSwap16(uint16_t value) {
	uint16_t buffer = value >> 8;	//AABB -> 00AA
	buffer |= (value & 0xFF) << 8;	//--BB -> BB00
	return buffer;					//00AA | BB00 -> BBAA
}

uint32_t endianSwap32(uint32_t value) {
	uint32_t buffer = (value & 0xFF) << 24; //AABBCCDD -> DD000000
	buffer |= (value & 0xFF00) << 8;		//----CC-- -> DDCC0000
	buffer |= (value >> 8) & 0xFF00;		//----BB-- -> DDCCBB00
	buffer |= value >> 24;					//------AA -> DDCCBBAA
	return buffer;
}

//Im getting sick. which means im also lazy. and its not like this is crucial to speed.
uint64_t endianSwap64(uint64_t value) {
	uint32_t lhs = endianSwap32(value >> 32);			//Swap [4-7]
	uint32_t rhs = endianSwap32(value & 0xFFFFFFFF);	//Swap [0-3]
	uint64_t buffer = (((uint64_t)rhs) << 32);	//Shift [0-3] to [4-7]
	return buffer | (uint64_t)lhs;				//Move swapped [4-7] to [0-3]
}