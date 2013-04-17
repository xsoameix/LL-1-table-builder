#include "Production.h"

Production* newP(Symbol *s) {
        return mNewP(s, mNULL);
}

Production* mNewP(Symbol *s, int reason) { // P = Production
        Production *p = (Production*) newMemoryLog(sizeof(Production), reason);
        p->S = mArrayNew(1, reason);
        mArrayAdd(p->S, s, reason);
        return p;
}

void addInWhichP(int NT_i, int P_i, Symbol *s) {
        NonTerminal *n = getNT()->item[NT_i];
        if(n->P->count < P_i + 1) {
                mArrayAdd(n->P, mNewP(s, mAIWP_nP), mAIWP_AA_P);
        } else {
                mArrayAdd(((Production*) n->P->item[P_i])->S, s, mAIWP_AA_S);
        }
}

void freeP(void *item) {
        Production *p = (Production*) item;
        for(int i = 0; i < p->S->count; i++) {
                mArrayFree(p->S, &freeS, mAIWP_nP);
        }
        freeMemoryLog(p, mAIWP_nP);
}
