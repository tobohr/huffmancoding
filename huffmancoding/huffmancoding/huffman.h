#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "strlib.h"
#include "constants.h"
#include "priority_queue.h"
#include "simpio.h"
#include "graphics.h"

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

typedef struct {
	int bits[30];
	int usedLength;
	char character;
	double freq;
}*huffmancodesT;

static int currenthuffman;
/*
* Function: nodecmp
* -----------------------------
* Function is used to compare NodeT
*/
int nodecmp(const void * a, const void * b);
/*
* Function: encpryptText
* -----------------------------
* The function encode txt with with huffmancoding based on the codes in array of 
* huffmancodes. used is the amount array postions used.
*/
void encpryptText(huffmancodesT codes[], string txt, int used);
/*
* Function: decryptText
* -----------------------------
* the function decodes the bitstring back to readable text and outputs it as the file decoded.txt
*/
void decryptText(nodeT root, string txt);
/*
* Function: computeCodes
* -----------------------------
* Travereses the huffmantree and saves the codes in huffmancodesT array
 */
void computeCodes(nodeT root, int arr[], int depth, huffmancodesT codes[]);
/*Function: writeHuff
* ---------------------------- 
* Writes huffman represention to file.
*/
void writeHuff(huffmancodesT huff, FILE *file);
/*Function: traverseTree
* ----------------------------
* traverses huffmantree bit by bit is used for decoding
*/
char traverseTree(nodeT root, string pattern, int* depth);
/*Function: printTree
* ----------------------------
*  !BROKEN!, Just Works on a small tree but hey its prints the Tree..
*/
void printTree(nodeT root, int arr[], int depth, bool Right);
/*Function: printArr
* ----------------------------
*  prints bit array
*/
void printArr(int arr[], int n);
/*Function: readFileToString
* ----------------------------
*  reads file from disk to string in memory
*/
char* readFileToString(string filepath);
/*Function: getFrequencyCharInTxt
* ----------------------------
*  Gets char frequency from txt string provided and adds it to priorityqueue
*/
void getFrequencyCharInTxt(string txt, priority_queue *pq);
/*Function: buildHuffmanTree
* ----------------------------
*  Builds huffmantree and return nodeT with the top of the tree.
*/
nodeT buildHuffmanTree(priority_queue *pq);
/*Function: buildHuffmanLeaf
* ----------------------------
*  helperfunction for buildHuffmanTree
*/
nodeT buildHuffmanLeaf(priority_queue *pq);
/*Function: readFreqFromFile
* ----------------------------
*  reads frequency from file line by line and save it to a priorityqueue
*/
void readFreqFromFile(string filename, priority_queue *pq);
/*Function: saveFileFreq
* ----------------------------
*  !BROKEN! Saves char frequency to file
*/
void saveFileFreq(huffmancodesT codes[], int count);