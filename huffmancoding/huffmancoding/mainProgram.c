#include "huffman.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main(void){
	char *txtfile, filename[20];
	nodeT* TEST;
	priority_queue *pq;
	pq = create_priority_queue(255, &nodecmp);
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	getFrequencyCharInTxtArray(txtfile,pq);
	TEST = buildHuffmanTree(pq);
	printf("test");
}
