#include "functions.h"


int main() {
    FILE *compress;
    if ((compress = fopen("../compFile.txt", "r")) == NULL)
    {
        printf("Error file\n");
        exit(1);
    }
    int numReplacements;
    char** wordsA;
    char** wordsB;
    wordsA = (char**)malloc(16*sizeof(char*));
    wordsB = (char**)malloc(16*sizeof(char*));
    reader(compress,&wordsA,&wordsB,&numReplacements);
    int length1 = print_wLength(wordsA,numReplacements)+ print_wLength(wordsB,numReplacements) + numReplacements*2;;
    fseek(compress,length1,SEEK_SET);
    FILE* decompress = fopen("../decompFile.txt", "w");
    print_compress(compress, decompress,wordsA,wordsB,numReplacements);
    fclose(compress);
    fclose(decompress);
    return 0;
}