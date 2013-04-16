#include "Symbol.h"

Symbol* newS_NT(NonTerminal *n) { // S = Symbol
        Symbol *s = (Symbol*) newMemory(sizeof(Symbol));
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
