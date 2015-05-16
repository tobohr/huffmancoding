#include "huffman.h"
//Reads file to string
char* readFileToString(string filepath){
	long length;
	FILE * file;
	char* fileAsString;
	int size, ret, read;
	file = fopen(filepath, "r");
	if (file != NULL)
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		rewind(file, 0);
		fileAsString = (char*)malloc(length+1);
		fread(fileAsString, sizeof(char), length, file);
		fileAsString[length + 1] = '\0';
		fclose(file);
	}
	return fileAsString;
}
nodeT* getFrequencyCharInTxtArray(string txt, int stringLength) {
	int i,j, temp, freq[30];
	queueADT queue;
	nodeT mynode;
	nodeT* Nodes = NewArray(30, nodeT);
	for (i = 0; i < 30; i++){
		freq[i] = 0;
		Nodes[i] = New(nodeT);
		Nodes[i]->charvalue.freq = 0;
	}
	for (i = 0; i < stringLength; i++){
		temp = txt[i] - 'a';
		freq[temp]++;
	}
	j = 0;
	queue = NewQueue();
	for (i = 0; i < 30; i++){
		if (freq[0] != 0){
			Nodes[j]->charvalue.freq = freq[i];
			Nodes[j]->charvalue.val = i + 'a';
			j++;
		}
	}
	qsort(Nodes, 30, sizeof(nodeT), nodecmp);
	return Nodes;
}
int intcmp(const void * a, const void * b)
{
	return (*(int*)b - *(int*)a);
}
int nodecmp(const void * a, const void * b)
{
	return ((*(nodeT*)b)->charvalue.freq - (*(nodeT*)a)->charvalue.freq);
}
symtabADT getFrequencyCharInTxt(string txt, int stringLength){
	int i;
	symtabADT symtab;
	symtab = NewSymbolTable();
	int value;
	char temp[2];
	for (i = 0; i < stringLength; i++){
		temp[0] = tolower(txt[i]);
		temp[1] = '\0';
		value = Lookup(symtab,temp);
		if (UNDEFINED == value){
			value = 1;
			Enter(symtab, temp, value);
		}
		else{
			value++;
			Enter(symtab, temp ,value);
		}
	}
	return symtab;
}
void buildHuffmanTree(nodeT* nodes, int nodeCount){
	int i,j;
	nodeT *mergequeue;
	nodeT node;
	j = 0;
	mergequeue = NewArray(30, nodeT);
	for (i = 0; i < nodeCount; i++){
		mergequeue[i]->charvalue.freq = NULL;
	}
	for (i = 0; i < nodeCount; i + 2){
		if (nodes[i]->charvalue.freq && mergequeue[j]->charvalue.freq == NULL){
			node = New(nodeT);
			node->children.leftchild = nodes[i];
			node->children.leftchild = nodes[i + 1];
			node->charvalue.freq = nodes[i]->charvalue.freq + nodes[i]->charvalue.freq;
			mergequeue[j] = node;
			j++;
		} else if (mergequeue[j]->charvalue.freq < nodes[i]->charvalue.freq){
		
		}
		  
	}
	
}