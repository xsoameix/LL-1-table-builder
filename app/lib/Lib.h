#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

void* newMemory(int size);
void freeMemory(void *ptr);
void checkMemory();
char* fileToStr(char *filename);
char* newSubStr(char *str, int offset, int len);
char* newCatStr(char *str_a, char *str_b);
char* newSpaces(int len);

#define MAX_LEN 512

#endif
