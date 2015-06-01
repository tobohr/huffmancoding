#include "huffman.h"

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
queueADT getFrequencyCharInTxtArray(string txt) {
	int i, j, temp, freq[255];
	queueADT queue;
	nodeT mynode;
	nodeT mynode2;
	nodeT* test;
	nodeT* Nodes = NewArray(255, nodeT);
	queue = NewQueue();
	int stringLength, amountofusedNodes;
	stringLength = StringLength(txt);
	for (i = 0; i < 255; i++){
		freq[i] = 0;
		Nodes[i] = New(nodeT);
		Nodes[i]->charvalue.freq = 0.0;
	}
	for (i = 0; i < stringLength; i++){
		temp = txt[i];
		freq[temp]++;
	}
	j = 0;
	amountofusedNodes = 0;
	for (i = 0; i < 255; i++){
		if (freq[i] != 0){
			Nodes[j]->charvalue.freq = (double)freq[i] / (double)stringLength;
			Nodes[j]->charvalue.val = i;
			Nodes[j]->nodetype = NodeLeaf;
			Nodes[j]->leftchild = NULL;
			Nodes[j]->rightchild = NULL;
			Enqueue(queue, Nodes[j]);
			j++;
			amountofusedNodes++;
		}
	}
	//qsort(Nodes, 30, sizeof(Nodes[0]), nodecmp);


	return queue;
}
int intcmp(const void * a, const void * b)
{
	return (*(int*)b - *(int*)a);
}
int nodecmp(const void * a, const void * b)
{
	return ((*(nodeT*)a)->charvalue.freq > (*(nodeT*)b)->charvalue.freq) - ((*(nodeT*)a)->charvalue.freq <(*(nodeT*)b)->charvalue.freq);

	//return ((*(nodeT*)a)->charvalue.freq < (*(nodeT*)b)->charvalue.freq) - ((*(nodeT*)a)->charvalue.freq >(*(nodeT*)b)->charvalue.freq);
}
int nodecmp2(const void * a, const void * b)
{
	return ((*(nodeT*)a)->charvalue.freq >(*(nodeT*)b)->charvalue.freq) - ((*(nodeT*)a)->charvalue.freq <(*(nodeT*)b)->charvalue.freq);

}
int isLeaf(nodeT root)
{
	return !(root->leftchild) && !(root->rightchild);
}
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	printf("\n");
}
void printCodes(nodeT root, int arr[], int top)
{
	nodeT child;
	// Assign 0 to left edge and recur
	if (root->leftchild)
	{
		child = root->leftchild;
		arr[top] = 0;
		printCodes(root->leftchild, arr, top + 1);
	}

	// Assign 1 to right edge and recur
	if (root->rightchild)
	{
		arr[top] = 1;
		printCodes(root->rightchild, arr, top + 1);
	}
	printf("%c: \n", root->charvalue);
	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (root->nodetype == NodeLeaf)
	{
		printf("%c: ", root->charvalue);
		printArr(arr, top);
	}
}
nodeT buildHuffmanTree(queueADT nodes){
	nodeT top;
	int arr[255], toasdp = 0;

	while (TRUE)
	{
		top = buildHuffmanLeaf(nodes);
		if (QueueIsEmpty(nodes)){
			break;
		}
	}
	printCodes(top, arr, toasdp);
	return top;
}
nodeT buildHuffmanLeaf(queueADT nodes){
	nodeT left, right,top;
	top = New(nodeT);
	left = Dequeue(nodes);
	right = Dequeue(nodes);
	top->leftchild = left;
	top->rightchild = right;
	top->nodetype = NodeParent;
	top->charvalue.val = 'P';
	top->charvalue.freq = left->charvalue.freq + right->charvalue.freq;
	if (QueueIsEmpty(nodes)){
		return top;
	}
	Enqueue(nodes, top);			
	return top;
	//med en fungerande priokö blir detta väldigt enkelt, eftersom nu går det ej att ta och något och lägga in de på samma plats till ex... hm
}
