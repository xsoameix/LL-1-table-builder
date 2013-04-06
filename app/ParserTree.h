#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <stdio.h>
#include "Token.h"

extern void buildTree(void (*parseFunc)(), char *treeType);
extern void addLeaf(Token *token);
extern void printSpaces();

#endif
