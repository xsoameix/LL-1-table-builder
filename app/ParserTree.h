#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <stdio.h>
#include "Token.h"
#include "Lib.h"
#include "Array.h"

typedef struct _Tree Tree;
struct _Tree {
        char *id;

        Tree *parent;

        // NonTerminal
        Array *child;

        // Terminal
        Array *leaves;
};

extern void buildRoot(void (*parseFunc)(), char *id);
extern void buildTree(void (*parseFunc)(), char *id);
extern void addChild(char *id);
extern void addLeaf(Token *token);
extern Tree* getRoot();

void enterTree();
void leaveTree();
Tree* newTree(char *id);
void printTreeType(char *treeType);
void printLeafId(char *id);

#endif
