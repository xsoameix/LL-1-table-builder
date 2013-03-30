#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

extern void* newMemory(int size);
extern char* fileToStr(char *filename);
extern char* newSubStr(char *str, int offset, int len);
