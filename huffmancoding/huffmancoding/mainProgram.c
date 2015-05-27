#include "huffman.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main(void){
	char *txtfile, temp[2], filename[20];
	int i, test;
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	queueADT que;
	que = getFrequencyCharInTxtArray(txtfile);
	buildHuffmanTree(que,11);
}
