#include "ParserTree.h"

Tree *tree = NULL;

int level = 0;

void buildRoot(void (*parseFunc)(), char *id) {
        printTreeType(id);
        level++;

        tree = newTree(id);
        (*parseFunc)();

        level--;
}

void buildTree(void (*parseFunc)(), char *id) {
        printTreeType(id);
        level++;

        addChild(id);

        // Simulate a tree
        enterTree();
        (*parseFunc)();
        leaveTree();

        level--;
}

void addChild(char *id) {
        assert(tree != NULL);
        if(tree->child == NULL) {
                tree->child = ArrayNew(1);
        }
        ArrayAdd(tree->child, newTree(id));
}

void addLeaf(Token *token) {
        printLeafId(token->id);
}

void enterTree() {
        Array *child = tree->child;
        tree = child->item[child->count - 1];
}

void leaveTree() {
        tree = tree->parent;
}

Tree* newTree(char *id) {
        Tree *t = (Tree*) newMemory(sizeof(Tree));
        t->id = id;
        t->parent = tree;
        t->child = NULL;
        t->leaves = NULL;
        return t;
}

void printTreeType(char *treeType) {
        printf("%s%s\n", newSpaces(level), treeType);
}

void printLeafId(char *id) {
        printf("%s\"%s\"\n", newSpaces(level), id);
}

Tree* getRoot() {
        return tree;
}
