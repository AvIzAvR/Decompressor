#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void reader(FILE*, char***, char***, int*);
void print_compress(FILE*,FILE*,char**,char**,int);
int print_wLength(char**, int);
