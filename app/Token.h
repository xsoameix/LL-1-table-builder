#ifndef TOKEN_H
#define TOKEN_H

#include "Lib.h"

// For Scanner & Parser
#define TOKEN 256
#define ARROW 257
#define OR    258
#define NONTERMINAL    259

typedef struct {
        char *id;
        int type;
} Token;

Token* newToken(char *id, int type);

#endif
