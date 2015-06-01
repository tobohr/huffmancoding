#include "huffman.h"
#include "constants.h"                  /* Contains constants */

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
void getFrequencyCharInTxtArray(string txt, priority_queue *pq) {
	int i, j, temp, freq[255];
	queueADT queue;
	nodeT mynode;
	nodeT mynode2;
	nodeT* test;
	int stringLength, amountofusedNodes;
	nodeT* Nodes = NewArray(255, nodeT);
	queue = NewQueue();
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
			mynode2 = New(nodeT);

			mynode2->charvalue.freq = (double)freq[i] / (double)stringLength;
			mynode2->charvalue.val = i;
			mynode2->nodetype = NodeLeaf;
			mynode2->leftchild = NULL;
			mynode2->rightchild = NULL;
			priority_queue_insert(pq, &mynode2);
			//heap_insert(&h, Nodes[j]->charvalue.val, Nodes[j]);
			//Enqueue(queue, mynode2);
			j++;
			amountofusedNodes++;
		}
	}

	test = priority_queue_poll(pq);

	//qsort(Nodes, 30, sizeof(Nodes[0]), nodecmp);


	return;
}
int intcmp(const void * a, const void * b)
{
	return (*(int*)b - *(int*)a);
}
//int comparator(const void *a, const void *b)
//{
//	nodeT value_1, value_2;
//
//	value_1 = *(nodeT*)a
//	value_2 = (*(nodeT*)b);
//
//	if (value_1 < value_2)
//	{
//		return SMALLER;
//	} else if (value_1 == value_2)
//	{
//		return EQUAL;
//	} else
//	{
//		return GREATER;
//	}
//}
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
	if (root->leftchild)
	{
		arr[top] = 1;
		printCodes(root->rightchild, arr, top + 1);
	}

	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (isLeaf(root))
	{
		printf("%c: ", root->charvalue);
		printArr(arr, top);
	}
}
nodeT buildHuffmanTree(priority_queue *pq){
	nodeT top;
	nodeT *tasd;
	int arr[255], toasdp = 0;
	toasdp = priority_queue_size(pq);
	tasd = priority_queue_poll(pq);
	while (TRUE)
	{
		top = buildHuffmanLeaf(pq);
		if (priority_queue_is_empty(pq)){
			break;
		}
	}
	printCodes(top, arr, toasdp);
	return top;
}
nodeT buildHuffmanLeaf(priority_queue *pq){
	nodeT *left,*right,top;
	top = New(nodeT);
	//left = Dequeue(nodes);
	left = priority_queue_poll(pq);
	right = priority_queue_poll(pq);
	//right = Dequeue(nodes);
	top->leftchild = left;
	top->rightchild = right;
	top->nodetype = NodeParent;
	top->charvalue.val = 'P';
//	top->charvalue.freq = left->charvalue.freq + right->charvalue.freq;
	if (priority_queue_is_empty(pq)){
		return top;
	}
	priority_queue_insert(pq, &top);
	//Enqueue(nodes, top);			
	return top;
	//med en fungerande priokö blir detta väldigt enkelt, eftersom nu går det ej att ta och något och lägga in de på samma plats till ex... hm
}
