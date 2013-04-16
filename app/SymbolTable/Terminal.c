#include "Terminal.h"

// Element type is Terminal.
static Array *gT; // g = global variable

void addT(Token *t) {
        if(gT == NULL) {
                gT = ArrayNew(1);
        }
        ArrayAdd(gT, newT(t));
}

Terminal* newT(Token *token) {
        Terminal *t = (Terminal*) newMemory(sizeof(Terminal));
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
