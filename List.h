#include <stdbool.h>
#include <stdio.h>
#include "Set.h"
#include "Lib.h"

typedef struct _List List;

typedef struct {
        int id;
        bool visited;
        List *pointTo_Front;
        List *pointTo_Back;
        Set result;
        bool done;
} Node;

struct _List {
        Node *node;
        List *next;
};

extern List* newList(Node *node);
extern Node* newNode(int id, int nodeLen);
extern Node** newNodeArray(int len);
extern void pushBack(Node *n, Node *next);
extern void printPointTo(Node **n, int nodeLen);
