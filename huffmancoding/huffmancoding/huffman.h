#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "strlib.h"
#include "constants.h"
#include "priority_queue.h"
#include "symtab.h"
#include "simpio.h"

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
}*huffmancodes;

void printTree2(nodeT root, int arr[], int depth, double x, double y, bool Right);
static int currenthuffman;
void writeArr(huffmancodes huff, FILE *file);

void encpryptText(huffmancodes codes[], string txt, int used);
void decryptText(nodeT root, string txt);

huffmancodes bitrep(huffmancodes codes[], int used, char character);
void computeCodes(nodeT root, int arr[], int top, huffmancodes codes[]);

char traverseTree(nodeT root, string pattern, int* depth);

void printCodes(nodeT root, int arr[], int top);
int nodecmp(const void * a, const void * b);
char* readFileToString(string filepath);
void getFrequencyCharInTxtArray(string txt, priority_queue *pq);
nodeT buildHuffmanTree(priority_queue *pq);
void readFreqFromFile(string filename, priority_queue *pq);
nodeT buildHuffmanLeaf(priority_queue *pq);
void printArr(int arr[], int n);
int intcmp(const void * a, const void * b);
