#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//#define mallocT(type, count) ((type*)malloc(count, sizeof(type)))
//#define callocT(type, count) ((type*)calloc(count, sizeof(type)))

/// @brief Opens a file with error handling
/// @param hndl The handle to the file if opened
/// @param path The file path to open
/// @param type the read mode
/// @return true if failed to open
int openFile(FILE** hndl, const char* path, const char* type);

/// @brief Strictly reads from a given file.
/// @param hndl The file to read from
/// @return The file data
char* readFile(FILE* hndl);

/// @brief Reads the contents of a file (fully managed)
/// @param buffer The destination buffer
/// @param path The file to read
/// @return true if failed to read
int readToBuffer(char** buffer, int* bufferSize, const char* path);


/// @brief Gets the file size in bytes
/// @param file The file
/// @return Size of file in bytes
int getFileSize(FILE* const file);