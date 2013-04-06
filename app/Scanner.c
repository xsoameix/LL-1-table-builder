#include "Scanner.h"

int forward = 0,
    lexemeBegin = 0;

Token* scan(char *string) {
        for(;; forward++, lexemeBegin++) {
                if(!isspace(string[forward])) {
                        break;
                }
        }

        int type;
        if(isArrow(string, forward)) {
                type = ARROW;
                forward += 2; // "->" == 2 chars
        } else if(isOr(string, forward)) {
                type = OR;
                forward++;
        } else if(isAlphaOrPunct(string, forward)) {
                if(isAtNewLine(string, forward)) {
                        type = NT;
                } else {
                        type = TOKEN;
                }
                while(isAlphaOrPunct(string, forward)) {
                        forward++;
                }
        } else if(isEOF(string, lexemeBegin)) {
                return NULL;
        }

        Token *token = (Token *) newMemory(sizeof(Token));
        token->id = newSubStr(string, lexemeBegin, forward - lexemeBegin); // char pointer point to file
        token->type = type;

        lexemeBegin = forward;
        return token;
}

bool isArrow(char *s, int offset) {
        return strncmp(&s[offset], "->", 2) == 0; // "->" == 2 chars
}

bool isOr(char *s, int offset) {
        return s[offset] == '|';
}

bool isAlphaOrPunct(char *s, int offset) {
        return isalpha(s[offset]) || ispunct(s[offset]);
}

bool isAtNewLine(char *s, int offset) {
        return offset == 0 || s[offset - 1] == 0x0A || s[offset - 1] == 0x0D;
}

bool isEOF(char *s, int offset) {
        return s[offset] == '\0';
}
