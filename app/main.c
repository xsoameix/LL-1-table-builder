#include <stdio.h>
#include "Lib.h"
#include "Scanner.h"
//#include "follow/Follow.h"

int main() {
        char *file = fileToStr("test.syntax");
        Token *token = NULL;
        token = scan(file);
        while(token != NULL) {
                printf("%s\n", token->id);
                token = scan(file);
        }
        //follow(5);
        return 0;
}
