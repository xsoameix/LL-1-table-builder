#include "Terminal.h"

static Terminal* newT(Token *token, int reason);

// Element type is Terminal.
static HTab *gT; // g = global variable
static bool gT_using = false;

void addT(Token *t) {
        if(!gT_using) {
                gT = newHashTable(3, mAT_nHT);
                gT_using = true;
        }
        if(HGet(gT, t->id) == NULL) {
                HPut(gT, t->id, newT(t, mAT_HP));
        } else { // Duplicate Terminal, free the id of token
                freeMemoryLog(t->id, mS_nSS);
        }
}

static
Terminal* newT(Token *token, int reason) {
        Terminal *t = (Terminal*) newMemoryLog(sizeof(Terminal), reason);
        t->id = token->id;
        return t;
}

HTab* getT() {
        return gT;
}

void free_gT() {
        Entry *e = gT->entry;
        for(int i = 0; i < gT->size; i++) {
                if(e[i].used) {
                        freeMemoryLog(e[i].key, mS_nSS);
                        freeMemoryLog(e[i].data, mAT_HP);
                }
        }
        freeMemoryLog(gT->entry, mAT_nHT);
        freeMemoryLog(gT, mAT_nHT);
}
