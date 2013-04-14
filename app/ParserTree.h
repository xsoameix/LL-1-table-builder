#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <stdio.h>
#include "Token.h"
#include "Lib.h"
#include "Array.h"

typedef struct _Tree Tree;
struct _Tree {
        // For nonTerminal
        char *id;

        // For terminal
        Token *token;

        Tree *parent;

        // NonTerminal & terminal, and element type is Tree.
        Array *child;
};

extern Tree *tree;

extern Tree* buildRoot(void (*parseFunc)(), char *id);
extern void buildTree(void (*parseFunc)(), char *id);
extern void addChild(char *id);
extern void addLeaf(Token *token);
extern void enterTree(void (*parseFunc)());
extern void enterWhichTree(void (*semanticFunc)(), int i);
extern void setTree(Tree *t);
extern Tree* getChild(int i);

Tree* newTree(char *id);
Tree* newLeaf(Token *t);
void printTreeType(char *treeType);
void printLeafId(char *id);

#endif
