#include "endian.h"
#include "fileCommon.h"
#include <stdio.h>
#include <stdlib.h>

//Usage: <exe> <16|32> <input file> <output file>
int main(int argc, const char* argv[]) {
	if(argc != 4) {
		printf("Usage: <exe> <stride: 16|32> <inputPath> <outputPath>\n");
		return 0;
	}
	int stride = atoi(argv[1]);
	const char* inputPath = argv[2];
	const char* outputPath = argv[3];

	//Read the input file
	char* buffer;
	int bufferSize;
	if(readToBuffer(&buffer, &bufferSize, inputPath)) {
		return -1;
	}

	if(stride == 16 && bufferSize & 1) {
		fprintf(stderr, "File wont align correctly to 16 bit pages. (%i bytes)\n", bufferSize);
		return -2;
	}
	if(stride == 32 && bufferSize & 3) {
		fprintf(stderr, "File wont align correctly to 32 bit pages. (%i bytes)\n", bufferSize);
		return -2;
	}

	char* converted = (char*)malloc(bufferSize);
	
	uint16_t* in_ptr16 = (uint16_t*)buffer;
	uint32_t* in_ptr32 = (uint32_t*)buffer;

	uint16_t* out_ptr16 = (uint16_t*)converted;
	uint32_t* out_ptr32 = (uint32_t*)converted;
	
	int elementCount = bufferSize / (stride / 8);
	for(int i = 0; i < elementCount; i++) {
		if(stride == 16) {
			out_ptr16[i] = swap16(in_ptr16[i]);
		} else {
			out_ptr32[i] = swap32(in_ptr32[i]);
		}
	}
	free(buffer);
	
	FILE* outputFile;
	if(openFile(&outputFile, outputPath, "wb")) {
		return -3;
	}
	fwrite(converted, sizeof(char), bufferSize, outputFile);
	fflush(outputFile);
	fclose(outputFile);
	free(converted);
	printf("Exported file successfully.\n");
	return 0;
}