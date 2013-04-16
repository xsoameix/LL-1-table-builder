#include "NonTerminal.h"

// Element type is NonTerminal.
static Array *gNT; // g = global variable

void addNT(Token *t) {
        if(gNT == NULL) {
                gNT = ArrayNew(1);
        }
        ArrayAdd(gNT, newNT(t));
}

NonTerminal* newNT(Token *t) {
        NonTerminal *n = (NonTerminal*) newMemory(sizeof(NonTerminal));
        n->no = gNT->count;
        n->id = t->id;
        n->P = ArrayNew(1);
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

void resetNT() {
        gNT = NULL;
}
