#ifndef ARRAY_H
#define ARRAY_H

#include "Lib.h"

typedef struct {
        int size; // size is >= count.
        int count; // count is the number of item used.
        void **item;
} Array;

Array* ArrayNew(int size);
void ArrayAdd(Array *a, void *item);

#endif
