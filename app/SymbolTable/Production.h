#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "../lib/Lib.h"
#include "../lib/Array.h"

typedef struct {
        // Element type is Symbol.
        Array *S;
} Production;

#include "NonTerminal.h"
#include "Symbol.h"

void addInWhichP(int NT_i, int P_i, Symbol *s);
void freeP(void *item);

#endif
