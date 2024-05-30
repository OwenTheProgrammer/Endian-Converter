#include "fileCommon.h"

int openFile(FILE** hndl, const char* path, const char* type) {
	*hndl = fopen(path, type);
	if(*hndl == NULL) {
		fprintf(stderr, "Failed to open file \"%s\".\n", path);
		return -1;
	}
	return 0;
}

char* readFile(FILE* hndl) {
	int fileSize = getFileSize(hndl);
	char* buffer = (char*)malloc(fileSize);
	fread(buffer, sizeof(char), fileSize, hndl);
	return buffer;
}

int readToBuffer(char** buffer, int* bufferSize, const char* path) {
	FILE* hndl;
	if(openFile(&hndl, path, "rb")) {
		return -1;
	}
	*buffer = readFile(hndl);
	*bufferSize = getFileSize(hndl);
	fclose(hndl);
	return 0;
}

int getFileSize(FILE* const file) {
	fseek(file, 0, SEEK_END);	//Go to end of file
	int size = (int)ftell(file);	//Get seek position
	fseek(file, 0, SEEK_SET);	//Return to the beginning of file
	return size;
}