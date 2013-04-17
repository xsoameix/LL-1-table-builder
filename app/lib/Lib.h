#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

enum {
        memLog_scan_newSubStr,
        memLog_scan_newToken,
        memLog_buildRoot_newTree,
        memLog_addChild_newTree,
        memLog_addChild_ArrayNew,
        memLog_addChild_ArrayAdd,
        memLog_addLeaf_newLeaf,
        memLog_addLeaf_ArrayNew,
        memLog_addLeaf_ArrayAdd,
        memLog_storeInWhichP_newS_NT,
        memLog_storeInWhichP_newS_T,
        memLog_addInWhichP_newP,
        memLog_addInWhichP_ArrayAdd_P,
        memLog_addInWhichP_ArrayAdd_S,
        memLog_addNT_newNT,
        memLog_addNT_ArrayNew,
        memLog_addNT_ArrayAdd,
        memLog_addT_newT,
        memLog_addT_ArrayNew,
        memLog_addT_ArrayAdd};

typedef struct {
        char *reason;
        int newMemoryCount;
        int freeMemoryCount;
} MemoryLog;

void* newMemory(int size);
void* newMemoryLog(int size, int reason);
void freeMemory(void *ptr);
void freeMemoryLog(void *ptr, int reason);
void checkMemory();
char* fileToStr(char *filename);
char* newSubStr(char *str, int offset, int len);
char* newSubStr_memLog(char *str, int offset, int len, int reason);
char* newCatStr(char *str_a, char *str_b);
char* newSpaces(int len);

#define MAX_LEN 512

#endif
