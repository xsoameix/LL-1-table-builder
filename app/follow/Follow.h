#ifndef FOLLOW_H
#define FOLLOW_H

#include <stdio.h>
#include <stdbool.h>
#include "Lib.h"
#include "List.h"
#include "Set.h"

Node** initFollow();
void DFS(Node *node);
void unvisit(Node **node);
void traversal(Node **node);
void follow(int nodeLength);

#endif
