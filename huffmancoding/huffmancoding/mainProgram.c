#include "huffman.h"


void main(void){
	char filename[20];
	int freq[30];
	char* txtfile;
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	symtabADT thefreq;
	char temp[2];
	int test;
	thefreq = getFrequencyCharInTxt(txtfile, 50);
	temp[0] = 'a';
	temp[1] = '\0';

	test = Lookup(thefreq, temp);
	printf("%d \n", test);

	/*getFrequencyCharInTxtArray(txtfile, 50, freq);
	int i;
	for (i = 0; i < 30; i++){
		printf("%d \n", freq[i]);
	}*/
}
