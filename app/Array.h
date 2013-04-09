#ifndef ARRAY_H
#define ARRAY_H

#include "Lib.h"

typedef struct {
        int size; // size is >= count.
        int count; // count is the number of item used.
        void **item;
} Array;

extern Array* ArrayNew(int size);
extern void ArrayAdd(Array *a, void *item);

#endif
