#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Lib.h"

typedef enum {
        HPUT;
        HGET;
} ACTION;

typedef struct {
        char *key;
        void *data;
} Entry;

// The reentrant has no static variable to maintain the state.
// So using this structure to maintain the state.

typedef struct {
        size_t used;
        Entry entry;
} _Entry;

#endif
