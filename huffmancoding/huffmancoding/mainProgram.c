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
static int pqsize;

static bool useFreqFromOtherFile = FALSE;
void main(void){
	menu();
	string *cmd;
	cmd = malloc(20 * sizeof(char));
	nodeT huffmantree;
	huffmancodes codes[200];
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
		priority_queue *pq;

		char *txtfile, filename[40], bits[120], top;
		int i, j, depth, Amountofbitsbefore, Amountofbits;
		string filename2;
		nodeT huffmantree;

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
		//codes = NewArray(pqsize, huffmancodes);
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
		
		/*Prints*/
		for (i = 0; i < pqsize; i++){
			printf("%c: ", codes[i]->character);
			printArr(codes[i]->bits, codes[i]->usedLength);
		}
		return huffmantree;
}

void getfreqWrap(string txtfile, priority_queue *pq){
	if (!useFreqFromOtherFile)
		getFrequencyCharInTxtArray(txtfile, pq);
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
saveFileFreqWrap(){

}
void decryptWrap(nodeT huffmantree){
	/*decrypt*/
	string encrypted;
	encrypted = readFileToString("huff.txt");
	decryptText(huffmantree, encrypted);
}
void menu(void){
	printf("\t\t Availible commands \n");
	printf("---------------------------------\n");
	printf("\t'codefile' to read file that you want to code with huffmancoding\n");
	printf("\t'decrypt' read file thats coded with huffman");
	printf("\t'comp-p' print compression rate\n");
	printf("\t'loadfreq' to load letterfreq from file\n");
	printf("\t'savefreq' to save letterfreq to file\n");
	printf("\tGood too know \n");
	printf("\tehhh..Nothing atm \n");
}