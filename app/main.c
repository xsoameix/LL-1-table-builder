#include "Lib.h"
#include "Parser.h"
#include "ParserTree.h"
#include "Semantic.h"

int tlevel = 0;

void printTreeId(char *id) {
        printf("%s%s\n", newSpaces(tlevel), id);
}

void DFS(Tree *t) {
        printTreeId(t->id == NULL ? t->token->id : t->id);
        tlevel++;
        if(t->child != NULL) {
                Array *child = t->child;
                for(int i = 0; i < child->count; i++) {
                        DFS(child->item[i]);
                }
        }
        tlevel--;
}

int main() {
        char *file = fileToStr("test.syntax");
        Tree *tree = parse(file);
        DFS(tree);
        semantic(tree);
        return 0;
}
