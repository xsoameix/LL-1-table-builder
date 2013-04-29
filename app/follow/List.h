#ifndef LIST_H
#define LIST_H

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

List* newList(Node *node);
Node* newNodeArray(int len);
void pushBack(Node *n, Node *next);
void printPointTo(Node *n, int nodeLen);

#endif
