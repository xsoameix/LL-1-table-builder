#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <stdio.h>
#include "lib/Lib.h"
#include "lib/Array.h"
#include "SymbolTable/Token.h"

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

Tree* buildRoot(void (*parseFunc)(), char *id);
void buildTree(void (*parseFunc)(), char *id);
void addChild(char *id);
void addLeaf(Token *token);
void enterTree(void (*parseFunc)());
void enterWhichTree(void (*semanticFunc)(), int i);
Tree* newTree(char *id);
Tree* mNewTree(char *id, int reason);
Tree* newLeaf(Token *t);
Tree* mNewLeaf(Token *token, int reason);
void setTree(Tree *t);
Tree* getTree();
Tree* getChild(int i);
void printTreeType(char *treeType);
void printLeafId(char *id);

#endif
