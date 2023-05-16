#include "functions.h"
#define SIZE_WORD 16


void reader(FILE* file, char*** wordsA, char*** wordsB, int* numReplacements) {
    int size = SIZE_WORD;
    char* word = (char*)calloc(size, sizeof(char));
    int i = 0;

    while (fscanf(file, "@%[^@\n]", word) == 1) {
        char* secondWord = (char*)calloc(size, sizeof(char));
        fscanf(file, "@%[^@\n]\n", secondWord);
        (*wordsA)[i] = (char*)calloc(strlen(word) + 1, sizeof(char));
        (*wordsB)[i] = (char*)calloc(strlen(secondWord) + 1, sizeof(char));
        strcpy((*wordsA)[i], word);
        strcpy((*wordsB)[i], secondWord);
        free(secondWord);
        i++;
        if (i == size) {
            size *= 2;
            *wordsA = (char**)realloc(*wordsA, size*sizeof(char*));
            *wordsB = (char**)realloc(*wordsB, size*sizeof(char*));
        }
        if (i == *numReplacements) {
            break;
        }
    }

    *numReplacements = i;
    free(word);

}

void print_compress(FILE* file,FILE* compressedFile, char** wordsA, char** wordsB, int numReplacements) {
    int size = SIZE_WORD;
    char* word = (char*)calloc(size,sizeof(char));

    while (fscanf(file, "%16s", word) == 1) {
        size_t len = strlen(word);

          if (ispunct(word[len - 1])) {
            char lastChar = word[len - 1];
            word[len - 1] = '\0';
            int found = 0;
            for (int i = 0; i < numReplacements; i++) {
                if (strcmp(word, wordsA[i]) == 0) {
                    fprintf(compressedFile, "%s%c ", wordsB[i], lastChar);
                    found = 1;
                    break;
                }
                else if (strcmp(word, wordsB[i]) == 0) {
                    fprintf(compressedFile, "%s%c ", wordsA[i], lastChar);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(compressedFile, "%s%c ", word, lastChar);
            }
    }
      else {
            int found = 0;
            for (int i = 0; i < numReplacements; i++) {
                if (strcmp(word, wordsA[i]) == 0) {
                    fprintf(compressedFile, "%s ", wordsB[i]);
                    found = 1;
                    break;
                }
                else if (strcmp(word, wordsB[i]) == 0) {
                    fprintf(compressedFile, "%s ", wordsA[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(compressedFile, "%s ", word);
            }
        }
    }
    free(word);
    fseek(compressedFile,0,SEEK_END);
    ftruncate(fileno(compressedFile), ftell(compressedFile) - 1);
}

int print_wLength(char** words, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += strlen(words[i]);
    }
    return sum;
}
