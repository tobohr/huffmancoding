#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "queue.h"
#include "strlib.h"
#include "constants.h"
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
void printCodes(nodeT root, int arr[], int top);
int nodecmp(const void * a, const void * b);
char* readFileToString(string filepath);
void getFrequencyCharInTxtArray(string txt, priority_queue *pq);
nodeT buildHuffmanTree(priority_queue *pq);
nodeT buildHuffmanLeaf(priority_queue *pq);
void printArr(int arr[], int n);
int intcmp(const void * a, const void * b);

