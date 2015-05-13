#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "symtab.h"

char* readFileToString(string filepath);
symtabADT getFrequencyCharInTxt(string txt, int stringLength);
void getFrequencyCharInTxtArray(string txt, int stringLength, int freq[]);
void buildHuffmanTree(symtabADT charfreq);
int intcmp(const void * a, const void * b);


union nodeval
{
	int value;
	string leaftype[20];
};
typedef struct node{
	union nodeval nodevalue;
	int *leafright;
	int *leafLeft;
};