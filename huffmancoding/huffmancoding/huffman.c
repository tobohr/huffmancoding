#include "huffman.h"
#include <stdio.h>
#include <string.h>
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
		rewind(file);
		fileAsString = (char*)malloc(length);
		fread(fileAsString, sizeof(char), length, file);
		fileAsString[length] = '\0';
		fclose(file);
	}
	return fileAsString;
}
void getFrequencyCharInTxtArray(string txt, priority_queue *pq) {
	int i, temp, freq[255];
	nodeT Newnode;
	int stringLength;
	stringLength = StringLength(txt);
	for (i = 0; i < 255; i++){ //intitalize freqtable to 0
		freq[i] = 0;
	}
	for (i = 0; i < stringLength; i++){//counts chars in string
		temp = txt[i];
		freq[temp]++;
	}
	for (i = 0; i < 255; i++){
		if (freq[i] != 0){
			Newnode = New(nodeT);
			Newnode->charvalue.freq = (double)freq[i] / (double)stringLength;
			Newnode->charvalue.val = CharToString(i);
			Newnode->nodetype = NodeLeaf;
			Newnode->leftchild = NULL;
			Newnode->rightchild = NULL;
			priority_queue_insert(pq, Newnode);
		}
	}
	return;
}
int nodecmp(const void * a, const void * b)
{
	nodeT value_1 = (nodeT *)a;
	nodeT value_2 = (nodeT *)b;
	if (value_1->charvalue.freq < value_2->charvalue.freq)
	{
		return SMALLER;
	} else if (value_1->charvalue.freq == value_2->charvalue.freq)
	{
		return EQUAL;
	} else
	{
		return GREATER;
	}
}
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	printf("\n");
}
void writeArr(huffmancodes huff, FILE *file)
{
	int i; char *code;
	code = malloc(sizeof(*code) * huff->usedLength);
	code[0] = 0;
	for (i = 0; i < huff->usedLength; ++i){
		strcat(code, IntegerToString(huff->bits[i]));
	}
	//should not be here..
	huff->bitrep = code;
	fputs(code, file);
	return;
}
void computeCodes(nodeT root, int arr[], int top, huffmancodes codes[]){
	// Assign 0 to left edge and recur
	if (root->leftchild)
	{
		arr[top] = 0;
		computeCodes(root->leftchild, arr, top + 1, codes);
	}
	// Assign 1 to right edge and recur
	if (root->rightchild)
	{
		arr[top] = 1;
		computeCodes(root->rightchild, arr, top + 1, codes);
	}
	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (root->nodetype == NodeLeaf)
	{
		int i;
		codes[currenthuffman] = New(huffmancodes);
		for (i = 0; i < top; i++){
			codes[currenthuffman]->bits[i] = arr[i];
		}
		codes[currenthuffman]->usedLength = top;
		codes[currenthuffman]->character = root->charvalue.val[0];
		currenthuffman++;
	}

}
void printTree(nodeT root, int arr[], int depth)
{
	int i;
	for (i = 0; i < 10-(2*depth); i++)
		printf(" ");
	// Assign 0 to left edge and recur
	if (root->leftchild)
	{
		printTree(root->leftchild, arr, depth + 1);
		for (i = 0; i < depth; i++)
			printf(" ");
		printf("%s \n","/");
	}
	// Assign 1 to right edge and recur
	if (root->rightchild)
	{
		printTree(root->rightchild, arr, depth + 1);
		for (i = 0; i < depth; i++)
			printf(" ");
		printf("%s \n", "\\");
	}
	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (root->nodetype == NodeLeaf)
	{
		printf("    %s ", root->charvalue.val);
		//printArr(arr, top);
	}
}
void printCodes(nodeT root, int arr[], int top)
{
	// Assign 0 to left edge and recur
	if (root->leftchild)
	{
		printf("/\n");
		arr[top] = 0;
		printCodes(root->leftchild, arr, top + 1);
	}
	// Assign 1 to right edge and recur
	if (root->rightchild)
	{
		printf("\\\n");
		arr[top] = 1;
		printCodes(root->rightchild, arr, top + 1);
	}
	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (root->nodetype == NodeLeaf)
	{
		printf("%s: ", root->charvalue.val);
		printArr(arr, top);
	}
}
nodeT buildHuffmanTree(priority_queue *pq){
	nodeT top;
	int arr[30], depth, pqsize;
	pqsize = priority_queue_size(pq);
	while (TRUE)
	{
		top = buildHuffmanLeaf(pq);
		if (priority_queue_is_empty(pq)){
			break;
		}
	}
	return top;
} 
nodeT buildHuffmanLeaf(priority_queue *pq){
	nodeT left,right,top;
	top = New(nodeT);
	left = (nodeT *)priority_queue_poll(pq);
	right = (nodeT *)priority_queue_poll(pq);
	top->leftchild = left;
	top->rightchild = right;
	top->nodetype = NodeParent;
	top->charvalue.val = Concat(left->charvalue.val, right->charvalue.val);
	top->charvalue.freq = left->charvalue.freq + right->charvalue.freq;
	if (priority_queue_is_empty(pq)){
		return top;
	}
	priority_queue_insert(pq, top);
	return top;
}
/**/
void encpryptText(huffmancodes codes[], string txt, int used){
	int stringLength, i, j;
	FILE* file;
	string code;
	huffmancodes huff;
	file = fopen("huff.txt", "a");
	stringLength = StringLength(txt);
	for (i = 0; i < stringLength; i++){
		huff = bitrep(codes, used, txt[i]);
		if (huff != NULL){
			writeArr(huff,file);
		}
	}
	fclose(file);

}
huffmancodes bitrep(huffmancodes codes[], int used, char character){
	int i;
	for (i = 0; i < used; i++){
		if (codes[i]->character == character){
			return codes[i];
		}
	}
	return NULL;
}
huffmancodes charrep(huffmancodes codes[],string bitrep, int used){
	int i;
	for (i = 0; i < used; i++){
		if (codes[i]->bitrep == bitrep){
			return codes[i];
		}
	}
	return NULL;
}
void decryptText(nodeT root, string txt){

	int stringLength, i, j, *depth;
	char character;
	FILE* file;
	depth = malloc(sizeof(int));
	(*depth) = 0;
	stringLength = StringLength(txt);
	for (i = 0; (*depth) < stringLength; i++){
		file = fopen("decode.txt", "a");
		character = traverseTree(root, txt, depth);
		fputc(character, file);
		fclose(file);
	}
}
char traverseTree(nodeT root, string pattern, int* depth){ 
	int bit;
	if (root->nodetype == NodeLeaf)
		return root->charvalue.val[0];
	bit = getBit(pattern, (*depth));
	(*depth)++;
	if (bit == 0){
		traverseTree(root->leftchild, pattern, depth);
	}
	else if (bit == 1)
		traverseTree(root->rightchild, pattern, depth);
}
int getBit(string encpryptetext, int index){
	if (encpryptetext[index] == 48)
		return 0;
	else if (encpryptetext[index] == 49)
		return 1;
	else
		return-1;
}
void readFreqFromFile(string filename, priority_queue *pq){
	FILE * file;
	string line, freq;
	nodeT nodeleaf;
	file = fopen(filename, "r");
	while (TRUE)
	{
		line = ReadLine(file);
		if (line == NULL) break;
		nodeleaf = New(nodeT);
		nodeleaf->charvalue.val = CharToString(line[0]);
		nodeleaf->charvalue.freq = StringToReal(SubString(line, 2, 6));
		nodeleaf->nodetype = NodeLeaf;
		nodeleaf->rightchild = NULL;
		nodeleaf->leftchild = NULL;
		priority_queue_insert(pq, nodeleaf);
	}
	fclose(file);
}