#include "Production.h"

Production* newP(Symbol *s) { // P = Production
        Production *p = (Production*) newMemory(sizeof(Production));
        p->S = ArrayNew(1);
        ArrayAdd(p->S, s);
        return p;
}

Production* newP_memLog(Symbol *s, int reason) { // P = Production
        Production *p = (Production*) newMemoryLog(sizeof(Production), reason);
        p->S = ArrayNew_memLog(1, reason);
        ArrayAdd_memLog(p->S, s, reason);
        return p;
}

void addInWhichP(int NT_i, int P_i, Symbol *s) {
        NonTerminal *n = getNT()->item[NT_i];
        if(n->P->count < P_i + 1) {
                ArrayAdd_memLog(n->P, newP_memLog(s, memLog_addInWhichP_newP), memLog_addInWhichP_ArrayAdd_P);
        } else {
                ArrayAdd_memLog(((Production*) n->P->item[P_i])->S, s, memLog_addInWhichP_ArrayAdd_S);
        }
}

void freeP(void *item) {
        Production *p = (Production*) item;
        for(int i = 0; i < p->S->count; i++) {
                ArrayFree(p->S, &freeS);
        }
        freeMemory(p);
}
