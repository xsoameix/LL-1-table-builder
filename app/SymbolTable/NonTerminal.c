#include "NonTerminal.h"

static NonTerminal* newNT(Token *t, int reason);
static void freeNT(void *item);

// Element type is NonTerminal.
static Array *gNT; // g = global variable
static bool gNT_using = false;

void addNT(Token *t) {
        if(!gNT_using) {
                gNT = mArrayNew(1, mAN_AN);
                gNT_using = true;
        }
        mArrayAdd(gNT, newNT(t, mAN_nN), mAN_AA);
}

static
NonTerminal* newNT(Token *t, int reason) {
        NonTerminal *n = (NonTerminal*) newMemoryLog(sizeof(NonTerminal), reason);
        n->no = gNT->count;
        n->id = t->id;
        n->P = mArrayNew(1, reason);
        return n;
}

// Usage: Get index of array of NonTerminals by name of NonTerminal.

int NT_IndexOf(Array *a, char *id) {
        for(int i = 0; i < a->count; i++) {
                if(strcmp(((NonTerminal*) a->item[i])->id, id) == 0) {
                        return i;
                }
        }
        return -1;
}

bool isNT(Token *t) {
        assert(gNT != NULL);
        for(int i = 0; i < gNT->count; i++) {
                if(strcmp(((NonTerminal*) gNT->item[i])->id, t->id) == 0) {
                        return true;
                }
        }
        return false;
}

Array* getNT() {
        return gNT;
}

void free_gNT() {
        mArrayFree(gNT, &freeNT, mAN_AN);
}

static
void freeNT(void *item) {
        NonTerminal *n = (NonTerminal*) item;
        freeMemoryLog(n->id, mS_nSS);
        for(int i = 0; i < n->P->count; i++) {
                mArrayFree(n->P, &freeP, mAN_nN);
        }
        freeMemoryLog(n, mAN_nN);
}
