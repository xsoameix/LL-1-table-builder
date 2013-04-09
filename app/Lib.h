#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define MAX_LEN 512

extern void* newMemory(int size);
extern void* freeMemory(void *ptr);
extern char* fileToStr(char *filename);
extern char* newSubStr(char *str, int offset, int len);
extern char* newSpaces(int len);

#endif
