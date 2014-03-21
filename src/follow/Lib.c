#include "Lib.h"

void* fNewMemory(int size) {
        void* ptr = malloc(size);
        assert(ptr != NULL);
        memset(ptr, 0, size);
        return ptr;
}
