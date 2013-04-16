#include "Production.h"

Production* newP(Symbol *s) { // P = Production
        Production *p = (Production*) newMemory(sizeof(Production));
        p->S = ArrayNew(1);
        ArrayAdd(p->S, s);
        return p;
}

void addInWhichP(int NT_i, int P_i, Symbol *s) {
        NonTerminal *n = getNT()->item[NT_i];
        if(n->P->count < P_i + 1) {
                ArrayAdd(n->P, newP(s));
        } else {
                ArrayAdd(((Production*) n->P->item[P_i])->S, s);
        }
}
