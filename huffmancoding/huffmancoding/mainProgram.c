#include "huffman.h"


void main(void){
	char filename[20];
	char* txtfile;
	printf("Enter filename");
	scanf("%s", &filename);
	txtfile = readFileToString(filename);
	printf("%s",txtfile);
}
