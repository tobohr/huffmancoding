#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "symtab.h"

char* readFileToString(string filepath);
symtabADT getFrequencyCharInTxt(string txt, int stringLength);
void getFrequencyCharInTxtArray(string txt, int stringLength, int freq[]);
void buildHuffmanTree(symtabADT charfreq);