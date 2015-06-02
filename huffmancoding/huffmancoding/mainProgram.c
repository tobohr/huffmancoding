#include "huffman.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main(void){
	char *txtfile, filename[20], bits[30], top;
	int i,j, pqsize, depth;
	nodeT huffmantree;
	huffmancodes *codes;
	priority_queue *pq;
	string encrypted;
	/* set intial value and stuff*/
	pq = create_priority_queue(255, &nodecmp);
	depth = 0;
	/* text input */
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	getFrequencyCharInTxtArray(txtfile,pq);
	
	pqsize = priority_queue_size(pq);
	huffmantree = buildHuffmanTree(pq);
	
	codes = NewArray(pqsize, huffmancodes);
	currenthuffman = 0;
	computeCodes(huffmantree, bits, depth, codes);

	encrypted = encpryptText(codes, txtfile, pqsize);

	//txtfile = readFileToString("kod.txt");

	decryptText(codes, encrypted, pqsize);
	for (i = 0; i < pqsize; i++){
		printf("%c: ", codes[i]->character);
		printArr(codes[i]->bits, codes[i]->usedLength);
	}



	scanf("%s", &filename);
}
