#include "fileCommon.h"

int openFile(FILE** hndl, const char* path, const char* type) {
	*hndl = fopen(path, type);
	if(*hndl == NULL) {
		fprintf(stderr, "Failed to open file \"%s\".\n", path);
		return -1;
	}
	return 0;
}

char* readFile(FILE* hndl, int size) {
	int fileBytes = getFileSize(hndl);
	int alloc = (size == 0) ? fileBytes : size;
	char* buffer = (char*)malloc(alloc);
	if(alloc > fileBytes) alloc = fileBytes;
	fread(buffer, sizeof(char), size, hndl);
	return buffer;
}

int readToBuffer(char** buffer, int* bufferSize, const char* path) {
	FILE* hndl;
	if(openFile(&hndl, path, "rb")) {
		return -1;
	}
	*buffer = readFile(hndl, 0);
	*bufferSize = getFileSize(hndl);
	fclose(hndl);
	return 0;
}

int getFileSize(FILE* const file) {
	fseek(file, 0, SEEK_END);
	int size = (int)ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

int writeFile(char* const buffer, int bufferSize, const char* path) {
	FILE* outputFile;
	if(openFile(&outputFile, path, "wb")) {
		fprintf(stderr, "Failed to write to file \"%s\".\n", path);
		return -1;
	}
	fwrite(buffer, sizeof(char), bufferSize, outputFile);
	fflush(outputFile);
	fclose(outputFile);
	return 0;
}