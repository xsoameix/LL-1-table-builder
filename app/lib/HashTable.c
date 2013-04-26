#include "HashTable.h"

static bool isprime(size_t n);
static bool HSearch(HTab *h, char *key, void *data, void **retdata, ACTION action);
static void rehash(HTab *h);

HTab* mNewHashTable(int size, int reason) {
        size |= 1; // Because most prime is odd, so make it odd.
        if(!isprime(size)) {
                size += 2;
        }
        HTab *h = newMemoryLog(sizeof(HTab), reason);
        h->size = size;
        h->filled = 0;
        h->entry = newMemoryLog(size * sizeof(Entry), reason);
        return h;
}

static
bool isprime(size_t n) {
        size_t div = 3;
        while(div * div < n && n % div != 0) {
                div += 2;
        }
        return n % div != 0;
}

bool HPut(HTab *h, char *key, void *data) {
        return HSearch(h, key, data, NULL, HPUT);
}

void* HGet(HTab *h, char *key) {
        void *result;
        if(HSearch(h, key, NULL, &result, HGET)) {
                return result;
        }
        return NULL;
}

static
bool HSearch(HTab *h, char *key, void *data, void **retdata, ACTION action) {
        size_t len = strlen(key),
               hval = len;
        for(int i = 0; i < len; i++) {
                hval <<= 4;
                hval += key[i];
        }

        size_t idx = hval % h->size; // First hash function.

        // There are 3 possibilities:
        // 1. The slot is used, same key.
        // 2. The slot is used, different key.
        // 3. The slot is not used.

        // Possibility 1.
        if(h->entry[idx].used == hval &&
                        strcmp(key, h->entry[idx].key) == 0) {
        // Possibility 2.
        } else if(h->entry[idx].used) {
                // The second hash function can't be 0.
                size_t hval2 = 1 + hval % (h->size - 1),
                       first_idx = idx;
                do {
                        idx = (idx + hval2) % h->size;
                        if(idx == first_idx) {
                                // If all of slots are Possibility 2. The end is here.
                                return false;
                        }

                        // Possibility 1.
                        if(h->entry[idx].used == hval &&
                                        strcmp(key, h->entry[idx].key) == 0) {
                                break;
                        }
                // Possibility 2.
                } while(h->entry[idx].used);
        }
        // Possibility 1, 3.
        Entry *select = &h->entry[idx];
        switch(action) {
        case HPUT:
                // Possibility 3.
                if(!select->used) {
                        h->filled++;
                }
                select->used = hval;
                select->key = key;
                select->data = data;
                float ratio = 0.8;
                if(((float) h->filled) / h->size > ratio) {
                        rehash(h);
                }
                break;
        case HGET:
                // Possibility 3.
                if(!select->used) {
                        return false;
                }
                // Possibility 1.
                *retdata = select->data;
                break;
        }
        return true;
}

static
void rehash(HTab *h) {
        size_t oldSize = h->size;
        // Make the new size is double and odd.
        size_t newSize = oldSize * 2 + 1;
        while(!isprime(newSize)) {
                newSize += 2;
        }
        h->size = newSize;

        h->filled = 0;

        // Create the new entry array.
        Entry *oldE = h->entry;
        h->entry = (Entry*) newMemoryLog(newSize * sizeof(Entry), mNULL);
        for(int i = 0; i < oldSize; i++) {
                if(oldE[i].used) {
                        HPut(h, oldE[i].key, oldE[i].data);
                }
        }
        freeMemoryLog(oldE, mNULL);
}

Array* HToArray(HTab *h) {
}
