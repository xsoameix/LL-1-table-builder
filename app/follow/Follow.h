#include <stdio.h>
#include <stdbool.h>
#include "Lib.h"
#include "List.h"
#include "Set.h"

extern Node** initFollow();
extern void DFS(Node *node);
extern void unvisit(Node **node);
extern void traversal(Node **node);
extern void follow(int nodeLength);
