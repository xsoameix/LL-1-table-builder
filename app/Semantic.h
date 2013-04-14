#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ParserTree.h"
#include "SymbolTable.h"

extern void semantic(Tree *t);

void PS_storeNTs();
void P_storeNTs();
void PS_storeTs();
void P_storeTs();
void STMTS_storeTs();
void STMTS__storeTs();
void TOKENS_storeTs();

#endif
