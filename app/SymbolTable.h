#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "lib/Array.h"
#include "SymbolTable/Token.h"
#include "SymbolTable/NonTerminal.h"
#include "SymbolTable/Terminal.h"
#include "SymbolTable/Symbol.h"
#include "SymbolTable/Production.h"

void storeNT(Token *t);
void storeT(Token *t);
void storeInWhichP(int NT_i, int P_i, int type, Token *tk);

#endif
