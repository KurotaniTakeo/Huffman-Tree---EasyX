#include "import.h"
#include <string>

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
	std::ifstream inFile(filename);
	if (!inFile) {
		std::cerr << "无法打开文件进行读操作: " << filename << std::endl;
		return;
	}

	// 读取节点总数
	char ttnode[5] = "";
	inFile.getline(ttnode, 256);
	totalNodes = atoi(ttnode);

	int m = 2 * totalNodes - 1;
	HT = new HTNode[m + 1]; 

	for (int i = 1; i <= totalNodes; ++i)
	{
		char treenode[20] = "";
		inFile.getline(treenode, 20);

	}

	// Init the rest of the nodes
	for (int i = totalNodes + 1; i <= m; ++i)
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		HT[i].ch[0] = '\0'; // Character field for non-leaf nodes set to '\0'
	}

	for (int i = 1; i <= totalNodes; i++)
	{

	}

	inFile.close();
}