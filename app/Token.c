#include "Token.h"

Token* newToken(char *id, int type) {
        Token *t = (Token *) newMemory(sizeof(Token));
        t->id = id; // char pointer point to file
        t->type = type;
        return t;
}
