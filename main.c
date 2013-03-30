#include <stdio.h>
#include "Lib.h"
#include "Scanner.h"

int main() {
        char *file = fileToStr("test.syntax");
        Token *token = NULL;
        token = scan(file);
        while(token != NULL) {
                printf("%s\n", token->id);
                token = scan(file);
        }
        return 0;
}
