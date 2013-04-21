#include "HashTable.h"

Array* mNewHashTable(int size, reason) {
        size |= 1; // Because most prime is odd, so make it odd.
        if(!isprime(size)) {
                size += 2;
        }
        Array *a = mArrayNew(size, reason);
        return a;
}

bool isprime(int n) {
}

_Entry* mNew_Entry(char *key, void *data, int reason) {
        _Entry *e = (_Entry*) newMemoryLog(sizeof(_Entry), reason);
        e->used = NULL;
        e->entry.key = key;
        e->entry.data = reason;
        return e;
}

bool HPut(Array *a, char *key, void *data) {
        Entry item = {key, data};
        return HSearch(a, item, NULL, HPUT);
}

void* HGet(Array *a, char *key) {
        Entry item = {key, NULL};
        Entry *result;
        if(HSearch(a, &item, result, HGET)) {
                return result->data;
        }
        return NULL;
}

bool HSearch(Array *a, Entry item, Entry *retval, ACTION action) {
        size_t len = strlen(item.key),
               hval;
        for(int i = 0; i < len; i++) {
                hval <<= 4;
                hval += item.key[i];
        }

        size_t idx = hval % a->size; // First hash function.
        if(a->item[idx]->used) { // The slot is used.
                // The second hash function can't be 0.
                size_t hval2 = 1 + hval % (size - 1),
                       first_idx = idx;
                do {
                        idx = (idx + hval2) % a->size;
                        if(idx == first_idx) {
                                return false;
                        }

                        // Found what we are finding.
                        if(((_Entry*) a->item[idx])->used == hval &&
                                        strcmp(key, ((_Entry*) a->item[idx])->entry.key) == 0) {
                                break;
                        }
                } while(a->item[idx]->used); // Collision happened.
        }
        switch(action) {
        case PUT:
                a->item[idx] = mNew_Entry(item.key, item.data, mHP_NE);
                break;
        case GET:
                *retval = ((Entry*) a->item[idx])->entry;
                break;
        }
        return true;
}
