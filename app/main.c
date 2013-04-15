#include "IntegrationTest/Parser.h"
#include "IntegrationTest/Semantic.h"
#include "UnitTest/minunit.h"
#include "UnitTest/SymbolTable.h"

int tests_run = 0;

int main() {
        // Integration Test

        char *path = "IntegrationTest/";
        Tree *t = IParser(path); // I = Integration Test
        ISemantic(t);

        // Unit Test

        char *result = USymbolTable(); // U = Unit Test
        if(result == 0) {
                printf("All test passed.\n");
        } else {
                printf("%s\n", result);
        }
        printf("Tests run: %d\n", tests_run);
        return result != 0;
}
