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
char* getFrequencyCharInTxt(string txt){

}