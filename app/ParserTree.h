#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <stdio.h>
#include "Token.h"
#include "Lib.h"

extern void buildTree(void (*parseFunc)(), char *treeType);
extern void addLeaf(Token *token);
extern void printTreeType(char *treeType);
extern void printLeafId(char *id);

#endif
