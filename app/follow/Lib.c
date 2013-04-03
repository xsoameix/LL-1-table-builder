#include "Lib.h"

void* newMemory(int size) {
        void* ptr = malloc(size);
        assert(ptr != NULL);
        memset(ptr, 0, size);
        return ptr;
}
