#include "endian.h"

uint16_t swap16(uint16_t value) {
	uint16_t buffer = value >> 8;	//AABB -> 00AA
	buffer |= (value & 0xFF) << 8;	//--BB -> BB00
	return buffer;					//00AA | BB00 -> BBAA
}

uint32_t swap32(uint32_t value) {
	uint32_t buffer = (value & 0xFF) << 24; //AABBCCDD -> DD000000
	buffer |= (value & 0xFF00) << 8;		//----CC-- -> DDCC0000
	buffer |= (value >> 8) & 0xFF00;		//----BB-- -> DDCCBB00
	buffer |= value >> 24;					//------AA -> DDCCBBAA
	return buffer;
}