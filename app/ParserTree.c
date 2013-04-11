#include "ParserTree.h"

Tree *tree = NULL;

int level = 0;

Tree* buildRoot(void (*parseFunc)(), char *id) {
        printTreeType(id);
        level++;

        tree = newTree(id);
        parseFunc();

        level--;

        return tree;
}

void buildTree(void (*parseFunc)(), char *id) {
        printTreeType(id);
        level++;

        addChild(id);

        // Simulate a tree
        enterTree(parseFunc);

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
        assert(tree != NULL);
        if(tree->child == NULL) {
                tree->child = ArrayNew(1);
        }
        ArrayAdd(tree->child, newLeaf(token));
        printLeafId(token->id);
}

void enterTree(void (*parseFunc)()) {
        // Enter Tree
        Array *child = tree->child;
        tree = child->item[child->count - 1];

        // Do something
        parseFunc();

        // Leave Tree
        tree = tree->parent;
}

Tree* newTree(char *id) {
        Tree *t = (Tree*) newMemory(sizeof(Tree));
        t->id = id;
        t->token = NULL;
        t->parent = tree;
        t->child = NULL;
        return t;
}

Tree* newLeaf(Token *token) {
        Tree *t = (Tree*) newMemory(sizeof(Tree));
        t->id = NULL;
        t->token = token;
        t->parent = tree;
        t->child = NULL;
        return t;
}

void setTree(Tree *t) {
        tree = t;
}

Token* getChildToken(int i) {
        assert(tree->child != NULL);
        return ((Tree*) tree->child->item[i])->token;
}

void printTreeType(char *treeType) {
        printf("%s%s\n", newSpaces(level), treeType);
}

void printLeafId(char *id) {
        printf("%s\"%s\"\n", newSpaces(level), id);
}
