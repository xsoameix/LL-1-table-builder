#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "Lib.h"
#include "Array.h"

typedef enum {
        HPUT,
        HGET
} ACTION;

typedef struct {
        size_t used;
        char *key;
        void *data;
} Entry;

typedef struct {
        size_t size;
        size_t filled;
        Entry *entry;
} HTab;

// The reentrant has no static variable to maintain the state.
// So using this structure to maintain the state.

HTab* mNewHashTable(int size, int reason);
bool HPut(HTab *h, char *key, void *data);
void* HGet(HTab *h, char *key);

#endif
