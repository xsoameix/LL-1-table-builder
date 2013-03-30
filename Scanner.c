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
                forward += 2; // "->" == 2 chars
                type = ARROW;
        } else if(isalpha(string[forward]) || ispunct(string[forward])) {
                while(isalpha(string[forward]) || ispunct(string[forward])) {
                        forward++;
                }
                type = TOKEN;
        } else if(string[lexemeBegin] == '\0') {
                return NULL;
        }

        Token *token = (Token *) newMemory(sizeof(Token));
        token->id = newSubStr(string, lexemeBegin, forward - lexemeBegin); // char pointer point to file
        token->type = type;

        lexemeBegin = forward;
        return token;
}
