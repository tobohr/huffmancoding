#include "huffman.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main(void){
	char *txtfile, temp[2], filename[20];
	int i, test;
	nodeT* TEST;
	priority_queue *pq;
	nodeT tasd ,*asd2,*asd34,*asd3e123;
	pq = create_priority_queue(255, &nodecmp);

	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	getFrequencyCharInTxtArray(txtfile,pq);
	TEST = buildHuffmanTree(pq);
	printf("test");
}
