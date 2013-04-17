#include "Token.h"

Token* newToken(char *id, int type) {
        Token *t = (Token *) newMemory(sizeof(Token));
        t->id = id; // char pointer point to file
        t->type = type;
        return t;
}

Token* newToken_memLog(char *id, int type, int reason) {
        Token *t = (Token *) newMemoryLog(sizeof(Token), reason);
        t->id = id; // char pointer point to file
        t->type = type;
        return t;
}

void freeToken(Token *t) {
        freeMemory(t->id);
        freeMemory(t);
}
