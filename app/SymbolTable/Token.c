#include "Token.h"

Token* newToken(char *id, int type) {
        return mNewToken(id, type, mNULL);
}

Token* mNewToken(char *id, int type, int reason) {
        Token *t = (Token *) newMemoryLog(sizeof(Token), reason);
        t->id = id; // char pointer point to file
        t->type = type;
        return t;
}

void freeToken(Token *t) {
        freeMemory(t->id);
        freeMemory(t);
}

void mFreeToken(Token *t) {
        freeMemoryLog(t->id, mS_nSS);
        freeMemoryLog(t, mS_nT);
}
