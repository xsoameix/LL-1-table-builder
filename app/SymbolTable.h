#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "Array.h"
#include "Token.h"

typedef struct {
        int no;
        char *id;

        // Element type is Production.
        Array *production;
} NonTerminal;

typedef struct {
        // Element type is Token.
        Array *token;
} Production;

extern void storeNonTerminal(Token *t);
extern void storeToken(Token *t);

#endif
