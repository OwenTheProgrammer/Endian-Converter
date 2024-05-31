#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/// @brief Opens a file with error handling
/// @param hndl Handle to the file if opened
/// @param path File path to open
/// @param type Read mode
/// @return true if failed to open
int openFile(FILE** hndl, const char* path, const char* type);

/// @brief Strictly reads from a given file.
/// @param hndl File to read from
/// @param size Amount of bytes to read. 0 calls getFileSize
/// @return File data
char* readFile(FILE* hndl, int size);

/// @brief Reads the contents of a file (fully managed)
/// @param buffer destination buffer
/// @param path File to read
/// @return true if failed to read
int readToBuffer(char** buffer, int* bufferSize, const char* path);

/// @brief Writes the contents of a buffer to a file (fully managed file-IO)
/// @param buffer Buffer to write to the file
/// @param bufferSize Size of the buffer
/// @param path Output file path
/// @return true if failed to write
int writeFile(char* const buffer, int bufferSize, const char* path);


/// @brief Gets the file size in bytes
/// @param file File in question
/// @return Size of file in bytes
int getFileSize(FILE* const file);