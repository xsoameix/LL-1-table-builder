#include "ParserTree.h"

int space = 0;

void buildTree(void (*parseFunc)(), char *treeType) {
        printSpaces();
        printf("parse_%s\n", treeType);

        // Simulate a tree
        //push(treeType);
        (*parseFunc)();
        //pop(treeType);

        space--;
}

void addLeaf(Token *token) {
}

void printSpaces() {
        for(int i = 0; i < space; i++) {
                printf("\t");
        }
        space++;
}
