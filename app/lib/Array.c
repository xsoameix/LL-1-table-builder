#include "Array.h"

Array* ArrayNew(int size) {
        return mArrayNew(size, mNULL);
}

Array* mArrayNew(int size, int reason) {
        Array *a = (Array*) newMemoryLog(sizeof(Array), reason);
        a->size = size;
        a->count = 0;
        a->item = (void**) newMemoryLog(size * sizeof(void*), reason);
        return a;
}

void ArrayAdd(Array *a, void *item) {
        mArrayAdd(a, item, mNULL);
}

void mArrayAdd(Array *a, void *item, int reason) {
        assert(a->count <= a->size);
        if(a->count == a->size) {
                int newSize = a->size * 2;
                void **newItem = (void**) newMemoryLog(newSize * sizeof(void*), reason);
                memcpy(newItem, a->item, a->size * sizeof(void*));
                freeMemory(a->item);
                a->item = newItem;
                a->size = newSize;
        }
        a->item[a->count++] = item;
}

void ArrayFree(Array *a, void (*freeFunc)(void*)) {
        assert(a != NULL);
        assert(freeFunc != NULL);
        ArrayEach(a, freeFunc);
        freeMemory(a->item);
        freeMemory(a);
}

void ArrayEach(Array *a, void (*func)(void*)) {
        for(int i = 0; i < a->count; i++) {
                func(a->item[i]);
        }
}