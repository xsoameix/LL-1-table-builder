#include <check.h>
#include <stdlib.h>
#include <libooc/object.h>

Suite * table_suite(void);

Suite *
ll1_suite(void) {
    return suite_create("ll1");
}

int
main(void) {
    SRunner * r = srunner_create(ll1_suite());
    srunner_add_suite(r, table_suite());
    srunner_run_all(r, CK_NORMAL);
    o_uint failed = srunner_ntests_failed(r);
    srunner_free(r);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
