#include "export.h"

void SaveHuffmanTreeToFile(HuffmanTree HT, int totalNodes, const char* filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "�޷����ļ�����д����: " << filename << std::endl;
		return;
	}

	// ����ڵ�����
	outFile << totalNodes << "\n";

	// ���浱ǰ�ڵ����Ϣ
	for (int i = 1; i <= 2 * totalNodes - 1; i++) {
		if (HT[i].ch[0] == '\0')
			outFile <<
			HT[i].weight << " " <<
			HT[i].parent << " " <<
			HT[i].lchild << " " <<
			HT[i].rchild << " " <<
			"--"<< endl;
		else if ((char)HT[i].ch[0] == 32)
			outFile <<
			HT[i].weight << " " <<
			HT[i].parent << " " <<
			HT[i].lchild << " " <<
			HT[i].rchild << " " <<
			"space" << endl;
		else
			outFile <<
			HT[i].weight << " " <<
			HT[i].parent << " " <<
			HT[i].lchild << " " <<
			HT[i].rchild << " " <<
			HT[i].ch[0] << endl;
	}
	outFile.close();
}

std::string replaceFileExtension(const std::string& filePath, const std::string& newExtension) {
	size_t dotPos = filePath.find_last_of(".");
	if (dotPos != std::string::npos) {
		return filePath.substr(0, dotPos + 1) + newExtension;
	}
	else {
		return filePath;  // No file extension found in the path
	}
}