#include "huffman.h"


void main(void){
	char *txtfile, temp[2], filename[20];
	int i, test;
	nodeT* Nodes;
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	symtabADT thefreq;
	Nodes = getFrequencyCharInTxtArray(txtfile, 50);
	buildHuffmanTree(Nodes,11);
	//thefreq = getFrequencyCharInTxt(txtfile, 50);
}
