#ifndef SYMBOL_H
#define SYMBOL_H

#include "../lib/Lib.h"
#include "Token.h"
#include "NonTerminal.h"
#include "Terminal.h"

typedef struct {
        int type; // NONTERMINAL or TERMINAL.
        NonTerminal *NT;
        Terminal *T;
} Symbol;

Symbol* newS_NT(NonTerminal *n);
Symbol* newS_T(Terminal *t);

#endif
