#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "symtab.h"
#include "queue.h"
#include "strlib.h"
#include "priority_queue.h"

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
int comparator(const void *a, const void *b);
void printCodes(nodeT root, int arr[], int top);
int nodecmp(const void * a, const void * b);
char* readFileToString(string filepath);
symtabADT getFrequencyCharInTxt(string txt, int stringLength);
void getFrequencyCharInTxtArray(string txt, priority_queue *pq);
nodeT buildHuffmanTree(priority_queue *pq);
nodeT buildHuffmanLeaf(priority_queue *pq, queueADT q);
void printArr(int arr[], int n);
int intcmp(const void * a, const void * b);
int intcmp3(const void * a, const void * b);

