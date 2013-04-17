#ifndef ARRAY_H
#define ARRAY_H

#include "Lib.h"

typedef struct {
        int size; // size is >= count.
        int count; // count is the number of item used.
        void **item;
} Array;

Array* ArrayNew(int size);
Array* mArrayNew(int size, int reason);
void ArrayAdd(Array *a, void *item);
void mArrayAdd(Array *a, void *item, int reason);
void ArrayFree(Array *a, void (*freeFunc)(void*));
void mArrayFree(Array *a, void (*freeFunc)(void*), int reason);
void ArrayEach(Array *a, void (*func)(void*));

#endif
