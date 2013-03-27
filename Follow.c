#include "Follow.h"

//Nodes array
Node** initFollow() {
        Node** n = newNodeArray(nodeLen);

        pushBack(n[0], n[4]);
        pushBack(n[0], n[7]);

        pushBack(n[1], n[0]);
        pushBack(n[1], n[2]);
        pushBack(n[1], n[3]);

        pushBack(n[3], n[1]);
        pushBack(n[3], n[2]);
        pushBack(n[3], n[7]);

        pushBack(n[4], n[6]);
        pushBack(n[4], n[7]);

        pushBack(n[5], n[4]);

        pushBack(n[6], n[5]);

        pushBack(n[7], n[5]);
        return n;
}

void DFS(Node *node) {
        node->visited = true;

        printf("follow(n[%d]):\n", node->id);

        // Increase the set of this node by DFS.
        if(node->pointTo_Front != NULL) {
                for(List *l = node->pointTo_Front; l != node->pointTo_Back->next; l = l->next) {
                        Node *pointTo = l->node;
                        if(!pointTo->visited) {
                                addElement(node->result, pointTo->id);
                                if(pointTo->done) {
                                        unionSet(done, pointTo->result, nodeLen);
                                } else if(!done[pointTo->id]) {
                                        printf(" n[%d] pointTo: %d\n", node->id, pointTo->id);
                                        DFS(pointTo);
                                }
                                unionSet(node->result, pointTo->result, nodeLen);
                        }
                }
        }

        printf(" n[%d]'s follow: ", node->id);
        printElements(node->result, nodeLen);
}

void unvisit(Node **node) {
        for(int i = 0; i < nodeLen; i++) {
                node[i]->visited = false;
        }
}

void traversal(Node **node) {
        done = (Set) newMemory(sizeof(Element) * nodeLen);
        for(int i = 0; i < nodeLen; i++) {
                printf("========n[%d]=======\n", i);
                DFS(node[i]);
                node[i]->done = true;
                unvisit(node);
                flushSet(done, nodeLen);
        }
}

void follow(int nodeLength) {
        nodeLen = nodeLength;
        Node **node = initFollow();
        printPointTo(node, nodeLen);
        traversal(node);
}
