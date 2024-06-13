#ifndef EXPORT_H
#define EXPORT_H

#include "huffman.h"
#include <fstream>

void SaveHuffmanTreeToFile(HuffmanTree HT, int totalNodes, const char* filename);
std::string replaceFileExtension(const std::string& filePath, const std::string& newExtension);
#endif