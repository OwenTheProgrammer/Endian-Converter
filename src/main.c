#include "endian.h"
#include "fileCommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Gets the amount of bytes up to the next stride
int getAlignmentPadding(int fileSize, int byteStride) {
	return (byteStride - fileSize) & (byteStride - 1);
}

//Usage: <exe> <16|32|64> <input file> <output file>
int main(int argc, const char* argv[]) {
	if(argc != 4) {
		printf("Usage: <exe> <stride: 16|32|64> <inputPath> <outputPath>\n");
		return 0;
	}
	int bitStride = atoi(argv[1]);
	const char* inputPath = argv[2];
	const char* outputPath = argv[3];

	//Open the input file and get its length in bytes
	FILE* inputFile;
	if(openFile(&inputFile, inputPath, "rb")) {
		return -1;
	}
	int bufferSize = getFileSize(inputFile);

	//Calculate how many bytes should be added to the end for alignment
	int byteStride = bitStride / 8;
	int eofPadding = getAlignmentPadding(bufferSize, byteStride);
	int outFileSize = bufferSize + eofPadding;
	if(eofPadding) {
		printf("Unaligned file size (%iB) padding with %iB to get (%iB)\n", bufferSize, eofPadding, outFileSize);
	}
	//Read file with extended padding if needed
	char* inputBuffer = readFile(inputFile, outFileSize);
	//Zero pad the ending of the buffer
	memset(inputBuffer + bufferSize, 0, eofPadding);

	//Calculate element count
	int elements = outFileSize / byteStride;
	char* outputBuffer = (char*)malloc(outFileSize);
	printf("Converting %i elements..\n", elements);

	for(int i = 0; i < elements; i++) {
		int offset = i * byteStride;

		char* in_ptr = inputBuffer + offset;
		char* out_ptr = outputBuffer + offset;

		//Swap based on stride
		switch(byteStride) {
			case 2: *(uint16_t*)out_ptr = ENDIAN_SWAP(*(uint16_t*)in_ptr);	break;
			case 4: *(uint32_t*)out_ptr = ENDIAN_SWAP(*(uint32_t*)in_ptr);	break;
			case 8: *(uint64_t*)out_ptr = ENDIAN_SWAP(*(uint64_t*)in_ptr);	break;
			default: 
				fprintf(stderr, "invalid conversion stride %i\n", bitStride);
				return -4;
		}
	}
	free(inputBuffer);
	
	if(writeFile(outputBuffer, outFileSize, outputPath)) {
		return -3;
	}
	free(outputBuffer);

	printf("Exported file successfully.\n");
	return 0;
}