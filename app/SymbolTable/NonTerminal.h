#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "assert.h"
#include "stdbool.h"
#include "../lib/Array.h"

typedef struct _NonTerminal {
        int no;
        char *id;

        // Element type is Production.
        Array *P;
} NonTerminal;

#include "Token.h"
#include "Production.h"

void addNT(Token *t);
NonTerminal* newNT(Token *t);
NonTerminal* mNewNT(Token *t, int reason);
int NT_IndexOf(Array *a, char *id);
bool isNT(Token *t);
Array* getNT();
void resetNT();
void freeNT(void *item);

#endif
