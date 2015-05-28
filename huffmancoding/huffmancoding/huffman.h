#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "symtab.h"
#include "queue.h"
#include "strlib.h"

typedef struct charvalueT {
	char val;
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
void printCodes(nodeT root, int arr[], int top);
int nodecmp(const void * a, const void * b);
char* readFileToString(string filepath);
symtabADT getFrequencyCharInTxt(string txt, int stringLength);
queueADT getFrequencyCharInTxtArray(string txt);
nodeT buildHuffmanTree(queueADT nodes);
nodeT buildHuffmanLeaf(queueADT nodes);
void printArr(int arr[], int n);
int intcmp(const void * a, const void * b);
int intcmp3(const void * a, const void * b);

