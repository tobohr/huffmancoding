#include "huffman.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void main(void){
	char *txtfile, filename[20], bits[30], top;
	int i,j, pqsize, depth;
	string filename2;
	nodeT huffmantree;
	huffmancodes *codes;
	symtabADT symtab;
	priority_queue *pq;
	string encrypted;
	/* set intial value and stuff*/
	pq = create_priority_queue(255, &nodecmp);
	depth = 0;
	/* input */
	printf("Enter filename ");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	filename2 = CopyString(filename);
	
	getFrequencyCharInTxtArray(txtfile,pq);
	//readFreqFromFile("engf.txt", pq);

	pqsize = priority_queue_size(pq); //Checks size before the queue gets dequeued..
	huffmantree = buildHuffmanTree(pq);
	/*Compute Codes*/
	codes = NewArray(pqsize, huffmancodes);
	currenthuffman = 0;
	computeCodes(huffmantree, bits, depth, codes);
	top = 0;
	txtfile = readFileToString(filename2);
	printTree(huffmantree, bits, top);
	/*encrypt*/
	encpryptText(codes, txtfile, pqsize);
	/*decrypt*/
	encrypted = readFileToString("kod.txt");
	decryptText(huffmantree, encrypted);

	for (i = 0; i < pqsize; i++){
		printf("%c: ", codes[i]->character);
		printArr(codes[i]->bits, codes[i]->usedLength);
	}



	scanf("%s", &filename);
}
