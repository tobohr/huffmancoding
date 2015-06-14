#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "strlib.h"
#include "constants.h"
#include "priority_queue.h"
#include "symtab.h"
#include "simpio.h"
#include "graphics.h"

typedef struct charvalueT {
	string val;
	double freq;
}charvalueT;

typedef struct {
	struct charvalueT charvalue;
	enum {
		NodeLeaf,
		NodeParent
	}nodetype;
	struct nodeT *leftchild;
	struct nodeT *rightchild;
}*nodeT;

typedef struct {
	int bits[30];
	int usedLength;
	char character;
	double freq;
}*huffmancodesT;

static int currenthuffman;

void writeHuff(huffmancodesT huff, FILE *file);
int nodecmp(const void * a, const void * b);

void encpryptText(huffmancodesT codes[], string txt, int used);
void decryptText(nodeT root, string txt);

huffmancodesT bitrep(huffmancodesT codes[], int used, char character);
void computeCodes(nodeT root, int arr[], int top, huffmancodesT codes[]);


char traverseTree(nodeT root, string pattern, int* depth);
void printCodes(nodeT root, int arr[], int top);
void printTree(nodeT root, int arr[], int depth, bool Right);

char* readFileToString(string filepath);
void getFrequencyCharInTxt(string txt, priority_queue *pq);

nodeT buildHuffmanTree(priority_queue *pq);
nodeT buildHuffmanLeaf(priority_queue *pq);

void readFreqFromFile(string filename, priority_queue *pq);
void saveFileFreq(huffmancodesT codes[], int count);

void printArr(int arr[], int n);
