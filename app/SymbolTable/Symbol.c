#include "Symbol.h"

Symbol* newS_NT(NonTerminal *n) { // S = Symbol
        Symbol *s = (Symbol*) newMemory(sizeof(Symbol));
        s->type = NONTERMINAL;
        s->NT = n;
        s->T = NULL;
        return s;
}

Symbol* newS_NT_memLog(NonTerminal *n, int reason) { // S = Symbol
        Symbol *s = (Symbol*) newMemoryLog(sizeof(Symbol), reason);
        s->type = NONTERMINAL;
        s->NT = n;
        s->T = NULL;
        return s;
}

Symbol* newS_T(Terminal *t) { // S = Symbol
        Symbol *s = (Symbol*) newMemory(sizeof(Symbol));
        s->type = TERMINAL;
        s->NT = NULL;
        s->T = t;
        return s;
}

Symbol* newS_T_memLog(Terminal *t, int reason) { // S = Symbol
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
        }
        freeMemory(item);
}
