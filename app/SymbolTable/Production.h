#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "../lib/Lib.h"
#include "../lib/Array.h"
#include "NonTerminal.h"
#include "Symbol.h"

typedef struct {
        // Element type is Symbol.
        Array *S;
} Production;

Production* newP(Symbol *s);
void addInWhichP(int NT_i, int P_i, Symbol *s);

#endif
