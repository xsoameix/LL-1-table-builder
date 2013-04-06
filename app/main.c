#include <stdio.h>
#include "Lib.h"
#include "Parser.h"

int main() {
        char *file = fileToStr("test.syntax");
        parse(file);
        return 0;
}
