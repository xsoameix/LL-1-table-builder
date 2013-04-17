#include "Symbol.h"

Symbol* newS_NT(NonTerminal *n) {
        return mNewS_NT(n, mNULL);
}

Symbol* mNewS_NT(NonTerminal *n, int reason) { // S = Symbol
        Symbol *s = (Symbol*) newMemoryLog(sizeof(Symbol), reason);
        s->type = NONTERMINAL;
        s->NT = n;
        s->T = NULL;
        return s;
}

Symbol* newS_T(Terminal *t) {
        return mNewS_T(t, mNULL);
}

Symbol* mNewS_T(Terminal *t, int reason) { // S = Symbol
        Symbol *s = (Symbol*) newMemoryLog(sizeof(Symbol), reason);
        s->type = TERMINAL;
        s->NT = NULL;
        s->T = t;
        return s;
}

void freeS(void *item) {
        Symbol *s = (Symbol*) item;
        if(s->type == TERMINAL) {
                freeT(s->T);
                freeMemoryLog(item, mSIWP_nS_T);
        } else {
                freeMemoryLog(item, mSIWP_nS_N);
        }
}
