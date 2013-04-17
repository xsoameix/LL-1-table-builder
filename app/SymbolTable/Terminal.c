#include "Terminal.h"

// Element type is Terminal.
static Array *gT; // g = global variable

void addT(Token *t) {
        if(gT == NULL) {
                gT = mArrayNew(1, mAT_AN);
        }
        mArrayAdd(gT, mNewT(t, mAT_nT), mAT_AA);
}

Terminal* newT(Token *token) {
        Terminal *t = (Terminal*) newMemory(sizeof(Terminal));
        t->no = gT->count;
        t->id = token->id;
        return t;
}

Terminal* mNewT(Token *token, int reason) {
        Terminal *t = (Terminal*) newMemoryLog(sizeof(Terminal), reason);
        t->no = gT->count;
        t->id = token->id;
        return t;
}

// Usage: Get index of array of Terminals by name of Terminal.

int T_IndexOf(Array *a, char *id) {
        for(int i = 0; i < a->count; i++) {
                if(strcmp(((Terminal*) a->item[i])->id, id) == 0) {
                        return i;
                }
        }
        return -1;
}

Array* getT() {
        return gT;
}

void freeT(Terminal *t) {
        freeMemory(t->id);
        freeMemory(t);
}
