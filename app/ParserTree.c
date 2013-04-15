#include "ParserTree.h"

static Tree *tree = NULL;

static int level = 0;

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
        enterWhichTree(parseFunc, tree->child->count - 1);
}

void enterWhichTree(void (*semanticFunc)(), int i) {
        // Enter Tree
        Array *child = tree->child;
        tree = child->item[i];

        // Do something
        semanticFunc();

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

Tree* getTree() {
        return tree;
}

Tree* getChild(int i) {
        assert(tree->child != NULL);
        return (Tree*) tree->child->item[i];
}

void printTreeType(char *treeType) {
        printf("%s%s\n", newSpaces(level), treeType);
}

void printLeafId(char *id) {
        printf("%s\"%s\"\n", newSpaces(level), id);
}
