#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>
#include "../lib/Lib.h"
#include "../lib/Array.h"
#include "../lib/HashTable.h"

typedef struct _Terminal {
        char *id;
} Terminal;

#include "Token.h"

#define TERMINAL 260

void addT(Token *t);
HTab* getT();
void free_gT();

#endif
