#include "huffman.h"
#include "genlib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include "graphics.h"

void menu(void);

void decryptWrap(nodeT huffmantree);
nodeT huffmancodeWrap(void);
void getfreqWrap(string txtfile, priority_queue *pq);
void Usefilefreq(void);
void printTree(nodeT root, int arr[], int depth, bool Right);

static bool useFreqFromOtherFile = FALSE;
static int pqsize;

void main(void){
	string *cmd;
	cmd = malloc(20 * sizeof(char));
	nodeT huffmantree;
	huffmancodes codes[200];
	menu();
	while (TRUE)
	{
		printf("Waiting for command \n");
		scanf("%s", cmd);
		if (StringEqual("codefile", cmd))
			huffmantree = huffmancodeWrap(codes);
		if (StringEqual("decrypt", cmd))
			decryptWrap(huffmantree); 
		if (StringEqual("loadfreq", cmd))
			Usefilefreq();
		if (StringEqual("savefreq", cmd))
			saveFileFreq(codes, pqsize);
		if (StringEqual("decrypt", cmd))
			decryptWrap(huffmantree);
	}
}
nodeT huffmancodeWrap(huffmancodes *codes){
		char *txtfile, filename[40], bits[120];
		int i, j, depth, Amountofbitsbefore, Amountofbits;
		string filename2;
		nodeT huffmantree;
		priority_queue *pq;

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
		currenthuffman = 0;
		computeCodes(huffmantree, bits, depth, codes);

		/*InitGraphics();
		MovePen(3.5, 3.5);
		printTree(huffmantree, bits, depth, FALSE);*/

		txtfile = readFileToString(filename2);
		/*encrypt*/
		encpryptText(codes, txtfile, pqsize);
		txtfile = readFileToString("huff.txt");

		Amountofbits = StringLength(txtfile);
		printf("Amountofbits After: %d \n", Amountofbits);
		printf("Compressionrateof %f \n", (double)Amountofbits/Amountofbitsbefore);
		
		/*Prints*/
		for (i = 0; i < pqsize; i++){
			printf("%c: ", codes[i]->character);
			printArr(codes[i]->bits, codes[i]->usedLength);
		}
		return huffmantree;
}

void getfreqWrap(string txtfile, priority_queue *pq){
	if (!useFreqFromOtherFile)
		getFrequencyCharInTxt(txtfile, pq);
	else{
		char filename[20];
		printf("Please enter filename for freqfile \n");
		scanf("%s", &filename);
		readFreqFromFile(filename, pq);
	}
}
void Usefilefreq(void){
	if (useFreqFromOtherFile){
		useFreqFromOtherFile = FALSE;
		printf("now using freq from based on inputfile \n");
	}
	else{
		useFreqFromOtherFile = TRUE;
		printf("now using freq from seprate freq-file \n");
	}
}
void decryptWrap(nodeT huffmantree){
	/*decrypt*/
	string encrypted;
	encrypted = readFileToString("huff.txt");
	decryptText(huffmantree, encrypted);
}
void menu(void){
	printf("\t\Availible commands \n");
	printf("---------------------------------\n");
	printf("'codefile' to read file that you want to code with huffmancoding\n");
	printf("'decrypt' read file thats coded with huffman\n");
	printf("'loadfreq' to load letterfreq from file\n");
	printf("'savefreq' to save letterfreq to file\n");
}
