#ifndef TERMINAL_H
#define TERMINAL_H

#include "../lib/Lib.h"
#include "../lib/Array.h"
#include "Token.h"

#define TERMINAL 260

typedef struct {
        int no;
        char *id;
} Terminal;

void addT(Token *t);
Terminal* newT(Token *token);
int T_IndexOf(Array *a, char *id);
Array* getT();

#endif
