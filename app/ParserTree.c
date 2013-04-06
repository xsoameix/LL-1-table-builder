#include "ParserTree.h"

int level = 0;

void buildTree(void (*parseFunc)(), char *treeType) {
        printTreeType(treeType);
        level++;

        // Simulate a tree
        //push(treeType);
        (*parseFunc)();
        //pop(treeType);

        level--;
}

void addLeaf(Token *token) {
        printLeafId(token->id);
}

void printTreeType(char *treeType) {
        printf("%s%s\n", newSpaces(level), treeType);
}

void printLeafId(char *id) {
        printf("%s\"%s\"\n", newSpaces(level), id);
}
