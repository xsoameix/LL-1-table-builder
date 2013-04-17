#include "Array.h"

Array* ArrayNew(int size) {
        Array *a = (Array*) newMemory(sizeof(Array));
        a->size = size;
        a->count = 0;
        a->item = (void**) newMemory(size * sizeof(void*));
        return a;
}

Array* ArrayNew_memLog(int size, int reason) {
        Array *a = (Array*) newMemoryLog(sizeof(Array), reason);
        a->size = size;
        a->count = 0;
        a->item = (void**) newMemoryLog(size * sizeof(void*), reason);
        return a;
}

void ArrayAdd(Array *a, void *item) {
        assert(a->count <= a->size);
        if(a->count == a->size) {
                int newSize = a->size * 2;
                void **newItem = (void**) newMemory(newSize * sizeof(void*));
                memcpy(newItem, a->item, a->size * sizeof(void*));
                freeMemory(a->item);
                a->item = newItem;
                a->size = newSize;
        }
        a->item[a->count++] = item;
}

void ArrayAdd_memLog(Array *a, void *item, int reason) {
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
