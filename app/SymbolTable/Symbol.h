#ifndef SYMBOL_H
#define SYMBOL_H

#include "../lib/Lib.h"

typedef struct _Symbol {
        int type; // NONTERMINAL or TERMINAL.
        struct _NonTerminal *NT;
        struct _Terminal *T;
} Symbol;

#include "Token.h"
#include "NonTerminal.h"
#include "Terminal.h"

Symbol* newS_NT(NonTerminal *n);
Symbol* newS_NT_memLog(NonTerminal *n, int reason);
Symbol* newS_T(Terminal *t);
Symbol* newS_T_memLog(Terminal *t, int reason);
void freeS(void *item);

#endif
