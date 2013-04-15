#include "Parser.h"

static void printTreeId(char *id);
static void printTree(Tree *t);

Tree* IParser(char *path) {
        char *filename = "test.syntax",
             *string = fileToStr(newCatStr(path, filename));
        Tree *tree = parse(string);
        printTree(tree);
        return tree;
}

static int level = 0;

static
void printTree(Tree *t) {
        printTreeId(t->id == NULL ? t->token->id : t->id);
        level++;
        if(t->child != NULL) {
                Array *child = t->child;
                for(int i = 0; i < child->count; i++) {
                        printTree(child->item[i]);
                }
        }
        level--;
}

static
void printTreeId(char *id) {
        printf("%s%s\n", newSpaces(level), id);
}
