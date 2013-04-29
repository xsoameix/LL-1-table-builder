#include "IntegrationTest/Parser.h"
#include "IntegrationTest/Semantic.h"
#include "IntegrationTest/follow/Follow.h"
#include "UnitTest/minunit.h"
#include "UnitTest/Array.h"
#include "UnitTest/SymbolTable.h"
#include "UnitTest/lib/HashTable.h"
#include "lib/Lib.h"

static char* run_unit_tests();

int tests_run = 0;

int main() {
        // Integration Test

        char *path = "IntegrationTest/";
        Tree *t = IParser(path); // I = Integration Test
        ISemantic(t);
        free_gNT();
        free_gT();

        // Unit Test

        char *result = run_unit_tests(); // U = Unit Test
        if(result == 0) {
                printf("All test passed.\n");
        } else {
                printf("%s\n", result);
        }
        printf("Tests run: %d\n", tests_run);

        // Check Memory

        checkMemory();
        return result != 0;
}

static
char* run_unit_tests() {
        //mu_run_test(USymbolTable);
        //mu_run_test(UArray);
        //mu_run_test(UHashTable);
        //mu_run_test(UFollow);
        return 0;
}
