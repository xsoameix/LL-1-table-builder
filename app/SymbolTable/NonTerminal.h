#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "assert.h"
#include "stdbool.h"
#include "../lib/Array.h"
#include "Token.h"

typedef struct {
        int no;
        char *id;

        // Element type is Production.
        Array *P;
} NonTerminal;

void addNT(Token *t);
NonTerminal* newNT(Token *t);
int NT_IndexOf(Array *a, char *id);
bool isNT(Token *t);
Array* getNT();
void resetNT();

#endif
