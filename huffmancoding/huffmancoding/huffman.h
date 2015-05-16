#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "symtab.h"
#include "queue.h"

typedef struct charvalueT {
	char val;
	int freq;
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
nodeT* getFrequencyCharInTxtArray(string txt, int stringLength);
void buildHuffmanTree(nodeT* nodes);
int intcmp(const void * a, const void * b);

