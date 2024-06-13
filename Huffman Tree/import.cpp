#define _CRT_SECURE_NO_WARNINGS 1
#include "import.h"
#include "GUI.h"
#include <string>
#include <sstream>

void readFromFile(char* filename, char* str)
{
	ifstream infile(filename);
	infile.getline(str, 256);
	infile.close();
}

int length(const char* str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

// Calculating the frequency of Character
void uniqueChars(const char* str, char* letter, int* freq)
{
	int kindnum = 0;
	int repeat = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		for (int j = 1; j <= kindnum; j++)
		{
			if (letter[j] == str[i])
			{
				freq[j]++;
				repeat = 1;
				break;
			}
			repeat = 0;
		}
		if (repeat == 0)
		{
			letter[kindnum] = str[i];
			freq[kindnum] = 1;
			kindnum++;
		}
	}
	letter[1 * MAX_STR_SIZE - 1] = '\0';
}

bool EndsWithExt(const std::string& str, const char* ext) {
	int extlen = length(ext);
	if (str.length() < extlen) {
		return false;
	}
	std::string lastFour = str.substr(str.length() - extlen);
	return lastFour == ext;
}

std::string ExtractFileNameWithoutExtension(const std::string& filePath) {
	// 查找最后一个路径分隔符的位置
	size_t lastSlashPos = filePath.find_last_of("\\/");
	size_t start = (lastSlashPos == std::string::npos) ? 0 : lastSlashPos + 1;

	// 查找文件名和后缀名之间的点的位置
	size_t lastDotPos = filePath.find_last_of(".");
	size_t end = (lastDotPos == std::string::npos || lastDotPos < start) ? filePath.length() : lastDotPos;

	// 提取并返回文件名（不含后缀名）
	return filePath.substr(start, end - start);
}

void LoadHuffmanTreeFromFile(HuffmanTree& HT, int& totalNodes, const char* filename) {
	ifstream inFile;
	inFile.open(filename, ios::in);
	status("Read from file SUCCESS!\nRead from file SUCCESS!");
	int n = 0;
	inFile >> totalNodes;
	int m = totalNodes * 2 - 1;
	cout << m << endl;
	HT = new HTNode[m + 1];
	char str[10] = "";
	for (int i = 1; i <= m; ++i)
	{
		inFile >> HT[i].weight;
		inFile >> HT[i].parent;
		inFile >> HT[i].lchild;
		inFile >> HT[i].rchild;
		inFile >> str;
		if (strcmp(str, "space") == 0)
		{
			HT[i].ch[0] = ' ';
			HT[i].ch[1] = '\0';
		}
		else if (strcmp(str, "--") == 0)
		{
			HT[i].ch[0] = '\0';
		}
		else
		{
			strcpy(HT[i].ch, str);
		}
		cout << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild << " " << HT[i].rchild << " " << HT[i].ch << endl;
	}
	inFile.close();
}