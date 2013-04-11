#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ParserTree.h"
#include "SymbolTable.h"

extern void semantic(Tree *t);

void semantic_PS();
void semantic_P();
void semantic_STMTS();
void semantic_STMTS_();
void semantic_TOKENS();

#endif
