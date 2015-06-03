#include "huffman.h"
#include "genlib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>

void menu(void);
void decryptWrap(nodeT huffmantree);
nodeT huffmancodeWrap(void);
void getfreqWrap(string txtfile, priority_queue *pq);
void Usefilefreq(void);

static bool useFreqFromOtherFile = FALSE;
void main(void){
	menu();
	string *cmd;
	cmd = malloc(20 * sizeof(char));
	nodeT huffmantree;

	while (TRUE)

	{
		printf("Waiting for command \n");
		scanf("%s", cmd);
		if (StringEqual("codefile", cmd))
			huffmantree = huffmancodeWrap();
		if (StringEqual("decrypt", cmd))
			decryptWrap(huffmantree);
		/*for (i = 0; i < pqsize; i++){
			printf("%c: ", codes[i]->character);
			printArr(codes[i]->bits, codes[i]->usedLength);
		}*/


	}
}
nodeT huffmancodeWrap(void){
		priority_queue *pq;

		char *txtfile, filename[40], bits[120], top;
		int i, j, pqsize, depth, Amountofbitsbefore, Amountofbits;
		string filename2;
		nodeT huffmantree;
		huffmancodes *codes;
		symtabADT symtab;

		/* set intial value and stuff*/
		pq = create_priority_queue(255, &nodecmp);
		depth = 0;
		/* input */
		printf("Enter filename ");
		scanf("%s", &filename);
		txtfile = readFileToString(filename);
		
		Amountofbitsbefore = 8*StringLength(txtfile);
		printf("Amountofbits before: %d \n", Amountofbitsbefore);

		filename2 = CopyString(filename);

		getfreqWrap(txtfile, pq);
		pqsize = priority_queue_size(pq); //Checks size before the queue gets dequeued..
		huffmantree = buildHuffmanTree(pq);
		/*Compute Codes*/
		codes = NewArray(pqsize, huffmancodes);
		currenthuffman = 0;
		computeCodes(huffmantree, bits, depth, codes);
		top = 0;
		txtfile = readFileToString(filename2);
		//printTree(huffmantree, bits, top);
		/*encrypt*/
		encpryptText(codes, txtfile, pqsize);

		txtfile = readFileToString("huff.txt");
		Amountofbits = StringLength(txtfile);
		printf("Amountofbits After: %d \n", Amountofbits);
		printf("Compressionrateof %f \n", (double)Amountofbits/Amountofbitsbefore);

		return huffmantree;
}

void getfreqWrap(string txtfile, priority_queue *pq){
	if (!useFreqFromOtherFile)
		getFrequencyCharInTxtArray(txtfile, pq);
	else
		readFreqFromFile("engf.txt", pq);
}
void Usefilefreq(void){
	if (useFreqFromOtherFile){
		useFreqFromOtherFile = FALSE;
		printf("set to false");
	}
	else{
		useFreqFromOtherFile = TRUE;
		printf("set to true");
	}
}
void decryptWrap(nodeT huffmantree){
	/*decrypt*/
	string encrypted;
	encrypted = readFileToString("huff.txt");
	decryptText(huffmantree, encrypted);
}
void menu(void){
	printf("Availible commands \n");

	printf("'codefile' to read file that you want to code with huffmancoding\n");
	printf("'decrypt' read file thats coded with huffman");

	printf("'comp-p' print compression rate\n");
	printf("'loadfreq' to load letterfreq from file\n");
	printf("'savefreq' to save letterfreq to file\n");

	printf("Good too know \n");
	printf("ehhh..Nothing atm \n");
}