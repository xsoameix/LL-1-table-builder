#ifndef TERMINAL_H
#define TERMINAL_H

#include "../lib/Lib.h"
#include "../lib/Array.h"

typedef struct _Terminal {
        int no;
        char *id;
} Terminal;

#include "Token.h"

#define TERMINAL 260

void addT(Token *t);
Terminal* newT(Token *token);
Terminal* mNewT(Token *token, int reason);
int T_IndexOf(Array *a, char *id);
Array* getT();
void freeT(Terminal *t);

#endif
