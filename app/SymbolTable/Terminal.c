#include "Terminal.h"

// Element type is Terminal.
static Array *gT; // g = global variable
static bool gT_using = false;

void addT(Token *t) {
        if(gT == NULL) {
                gT = mArrayNew(1, mAT_AN);
        }
        mArrayAdd(gT, mNewT(t, mAT_nT), mAT_AA);
        gT_using = true;
}

Terminal* newT(Token *token) {
        return mNewT(token, mNULL);
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

void resetT() {
        if(gT_using) {
                mArrayFree(gT, NULL, mAT_AN);
        }
}

void freeT(Terminal *t) {
        freeMemoryLog(t->id, mS_nSS);
        freeMemoryLog(t, mAT_nT);
}
