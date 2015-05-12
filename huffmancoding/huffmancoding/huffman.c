#include "huffman.h"
#include "symtab.h"
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
void getFrequencyCharInTxtArray(string txt, int stringLength, int freq[]){
	int i, temp;
	for (i = 0; i < 30; i++){
		freq[i] = 0;
	}
	for (i = 0; i < stringLength; i++){
		temp = txt[i] - 'a';
		freq[temp]++;
	}
}
void getFrequencyCharInTxt(string txt, int stringLength){

}