#include "Symbol.h"

Symbol* newS_NT(NonTerminal *n, int reason) { // S = Symbol
        Symbol *s = (Symbol*) newMemoryLog(sizeof(Symbol), reason);
        s->type = NONTERMINAL;
        s->NT = n;
        s->T = NULL;
        return s;
}

Symbol* newS_T(Terminal *t, int reason) { // S = Symbol
        Symbol *s = (Symbol*) newMemoryLog(sizeof(Symbol), reason);
        s->type = TERMINAL;
        s->NT = NULL;
        s->T = t;
        return s;
}

void freeS(void *item) {
        Symbol *s = (Symbol*) item;
        if(s->type == TERMINAL) {
                freeMemoryLog(item, mSIWP_nS_T);
        } else {
                freeMemoryLog(item, mSIWP_nS_N);
        }
}
