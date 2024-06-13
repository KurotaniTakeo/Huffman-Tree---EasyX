#ifndef IMPORT_H
#define IMPORT_H

#include "huffman.h"
#include <fstream>

void readFromFile(char* filename, char* str);

// Calculating the frequency of Character
void uniqueChars(const char* str, char* letter, int* freq);

bool EndsWithExt(const std::string& str, const char* ext);

int length(const char* str);

std::string ExtractFileNameWithoutExtension(const std::string& filePath);

void LoadHuffmanTreeFromFile(HuffmanTree& HT, int& totalNodes, const char* filename);


#endif