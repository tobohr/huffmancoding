#include "huffman.h"


void main(void){
	char filename[20];
	int freq[30];
	char* txtfile;
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	getFrequencyCharInTxt(txtfile, 50, freq);
	int i;
	for (i = 0; i < 30; i++){
		printf("%d \n", freq[i]);
	}
}
