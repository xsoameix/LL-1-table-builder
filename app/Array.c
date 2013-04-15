#include "Array.h"

Array* ArrayNew(int size) {
        Array *a = (Array*) newMemory(sizeof(Array));
        a->size = size;
        a->count = 0;
        a->item = (void**) newMemory(size * sizeof(void*));
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
