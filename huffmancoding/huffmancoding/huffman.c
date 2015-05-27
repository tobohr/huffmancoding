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
		fileAsString = (char*)malloc(length);
		fread(fileAsString, sizeof(char), length, file);
		fileAsString[length] = '\0';
		fclose(file);
	}
	return fileAsString;
}
nodeT* getFrequencyCharInTxtArray(string txt) {
	int i,j, temp, freq[30];
	queueADT queue;
	nodeT mynode;
	nodeT Nodes[30];
	int stringLength;
	stringLength = StringLength(txt);
	for (i = 0; i < 30; i++){
		freq[i] = 0;
		Nodes[i].charvalue.freq = 0;
	}
	for (i = 0; i < stringLength; i++){
		temp = txt[i] - 'a';
		freq[temp]++;
	}
	j = 0;
	queue = NewQueue();
	for (i = 0; i < 30; i++){
		if (freq[0] != 0){
			Nodes[j].charvalue.freq = (double)freq[i] / (double)stringLength;
			Nodes[j].charvalue.val = i + 'a';
			j++;
		}
	}
	qsort(Nodes, 30, sizeof(double), nodecmp);

	return Nodes;
}
int intcmp(const void * a, const void * b)
{
	return (*(int*)b - *(int*)a);
}
double nodecmp(const void * a, const void * b)
{
	double test;
	test = (*(nodeT)b).charvalue.freq - (*(nodeT)a).charvalue.freq;
	return (test);
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
	
	nodeT node;
	j = 0;
	nodeT *mergequeue = NewArray(30, nodeT);
	for (i = 0; i < nodeCount; i++){
		//mergequeue[i] = New(nodeT);
		//mergequeue[i]->charvalue.freq = NULL;
	}/*
	i = 0;
	while (i <= nodeCount){
		node = New(nodeT);
		if (mergequeue[j]->charvalue.freq == 0){
			node->children.leftchild = nodes[i];
			node->charvalue.freq = nodes[i]->charvalue.freq;
			i++;
			//select leftchild specalcase
		}
		else if (nodes[i]->charvalue.freq > mergequeue[j]->charvalue.freq){
			node->children.leftchild = nodes[i];
			node->charvalue.freq += nodes[i]->charvalue.freq;
			i++;
			//select leftchild
		} else{
			node->children.rightchild = mergequeue[j];
			node->charvalue.freq += mergequeue[i]->charvalue.freq;
			j++;
			//select leftchild
		}
		if (nodes[i]->charvalue.freq > mergequeue[j]->charvalue.freq){
			node->children.rightchild = nodes[i];
			node->charvalue.freq += nodes[i]->charvalue.freq;
			node->nodetype = NodeParent;
			i++;
			//select rightchild
		} else{
			node->children.rightchild = mergequeue[j];
			node->charvalue.freq += mergequeue[i]->charvalue.freq;
			node->nodetype = NodeParent;
			j++;
			//select rightchild
		}

		mergequeue[j] = node;
		//printf("%d \n", j);
		//printf("%d \n", i);
	}*/


}