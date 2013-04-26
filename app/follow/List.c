#include "List.h"

List* newList(Node *node) {
        List *list = (List*) fNewMemory(sizeof(List));

        list->node = node;
        list->next = NULL;

        return list;
}

Node* newNode(int id, int nodeLen) {
        Node *node = (Node*) fNewMemory(sizeof(Node));

        node->id = id;
        node->visited = false;
        node->pointTo_Front = NULL;
        node->pointTo_Back = NULL;
        node->result = (Set) fNewMemory(sizeof(Element) * nodeLen);
        node->done = false;

        return node;
}

Node** newNodeArray(int len) {
        Node **node = (Node**) fNewMemory(sizeof(Node*) * len);
        for(int i = 0; i < len; i++) {
                node[i] = newNode(i, len);
        }
        return node;
}

void pushBack(Node *n, Node *next) {
        List *l = newList(next);
        if(n->pointTo_Front == NULL) {
                n->pointTo_Front = l;
        } else {
                n->pointTo_Back->next = l;
        }
        n->pointTo_Back = l;
}

void printPointTo(Node **n, int nodeLen) {
        for(int i = 0; i < nodeLen; i++) {
                printf("n[%d]'s pointTo: ", i);

                // print n->pointTo list
                if(n[i]->pointTo_Front != NULL) {
                        for(List *l = n[i]->pointTo_Front; l != n[i]->pointTo_Back->next; l = l->next) {
                                printf("%d ", l->node->id);
                        }
                }

                printf("\n");
        }
}
