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
	union {
		struct node *leftchild;
		struct node *rightchild;
	}children;

}*nodeT;

int nodecmp(const void * a, const void * b);
char* readFileToString(string filepath);
symtabADT getFrequencyCharInTxt(string txt, int stringLength);
queueADT getFrequencyCharInTxtArray(string txt);
void buildHuffmanTree(nodeT* nodes, int nodeCount);
nodeT buildHuffmanLeaf(queueADT nodes, queueADT merge);
int intcmp(const void * a, const void * b);

