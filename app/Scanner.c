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
        if(strncmp(&string[forward], "->", 2) == 0) { // "->" == 2 chars
                type = ARROW;
                forward += 2; // "->" == 2 chars
        } else if(string[forward] == '|') {
                type = OR;
                forward++;
        } else if(isalpha(string[forward]) || ispunct(string[forward])) {
                if(forward == 0 || string[forward - 1] == 0x0A || string[forward - 1] == 0x0D) {
                        type = NT;
                } else {
                        type = TOKEN;
                }
                while(isalpha(string[forward]) || ispunct(string[forward])) {
                        forward++;
                }
        } else if(string[lexemeBegin] == '\0') {
                return NULL;
        }

        Token *token = (Token *) newMemory(sizeof(Token));
        token->id = newSubStr(string, lexemeBegin, forward - lexemeBegin); // char pointer point to file
        token->type = type;

        lexemeBegin = forward;
        return token;
}
