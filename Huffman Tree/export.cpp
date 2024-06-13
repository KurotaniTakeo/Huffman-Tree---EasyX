#include "export.h"

void SaveHuffmanTreeToFile(HuffmanTree HT, int totalNodes, const char* filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "无法打开文件进行写操作: " << filename << std::endl;
		return;
	}

	// 保存节点总数
	outFile << totalNodes << "\n";

	// 保存当前节点的信息
	for (int i = 1; i <= 2 * totalNodes - 1; i++) {
		if (HT[i].ch[0] == '\0')
			outFile <<
			HT[i].weight << " " <<
			HT[i].parent << " " <<
			HT[i].lchild << " " <<
			HT[i].rchild << " " <<
			"--" << " " << endl;
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