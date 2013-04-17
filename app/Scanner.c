#include "Scanner.h"

static bool isArrow(char *s, int offset);
static bool isOr(char *s, int offset);
static bool isAlphaOrPunct(char *s, int offset);
static bool isAtNewLine(char *s, int offset);
static bool isEOF(char *s, int offset);

static int forward = 0,
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
                        type = NONTERMINAL;
                } else {
                        type = TOKEN;
                }
                while(isAlphaOrPunct(string, forward)) {
                        forward++;
                }
        } else if(isEOF(string, lexemeBegin)) {
                return NULL;
        }

        Token *token = mNewToken(
                        mNewSubStr(string, lexemeBegin, forward - lexemeBegin, mS_nSS), // char pointer point to file
                        type,
                        mS_nT);

        lexemeBegin = forward;
        return token;
}

static
bool isArrow(char *s, int offset) {
        return strncmp(&s[offset], "->", 2) == 0; // "->" == 2 chars
}

static
bool isOr(char *s, int offset) {
        return s[offset] == '|';
}

static
bool isAlphaOrPunct(char *s, int offset) {
        return isalpha(s[offset]) || ispunct(s[offset]);
}

static
bool isAtNewLine(char *s, int offset) {
        return offset == 0 || s[offset - 1] == 0x0A || s[offset - 1] == 0x0D;
}

static
bool isEOF(char *s, int offset) {
        return s[offset] == '\0';
}
