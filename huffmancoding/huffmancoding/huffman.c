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
void buildHuffmanTree(symtabADT charfreq){

}