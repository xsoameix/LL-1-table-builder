#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

enum {
        mS_nSS, // m = memory log
        mS_nT,
        mBR_nT,
        mAC_nT,
        mAC_AN,
        mAC_AA,
        mAL_nL,
        mAL_AN,
        mAL_AA,
        mSIWP_nS_N,
        mSIWP_nS_T,
        mAIWP_nP,
        mAIWP_AA_P,
        mAIWP_AA_S,
        mAN_nN,
        mAN_AN,
        mAN_AA,
        mAT_nT,
        mAT_AN,
        mAT_AA};

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
