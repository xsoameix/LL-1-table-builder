#include <check.h>
#include <stdlib.h>
#include <signal.h>
#include <libooc/object.h>
#include "../src/ll1.h"

static char buf[BUFSIZ];

static void
catch_first_conflict_error(int signo) {
    char * err = "FirstConflictError:";
    ck_assert(strncmp(buf, err, strlen(err)) == 0);
    exit(EXIT_SUCCESS);
}

START_TEST(first_conflict_error) {
    signal(SIGABRT, catch_first_conflict_error);
    setbuf(stderr, buf);
    int argc = 2;
    char * argv[] = {"src/ll1", "../tests/first_conflict_example.syntax"};
    ll1_init(argc, argv);
} END_TEST

static void
catch_follow_conflict_error(int signo) {
    char * err = "FollowConflictError:";
    ck_assert(strncmp(buf, err, strlen(err)) == 0);
    exit(EXIT_SUCCESS);
}

START_TEST(follow_conflict_error) {
    signal(SIGABRT, catch_follow_conflict_error);
    setbuf(stderr, buf);
    int argc = 2;
    char * argv[] = {"src/ll1", "../tests/follow_conflict_example.syntax"};
    ll1_init(argc, argv);
} END_TEST

Suite *
table_suite(void) {
    Suite * s = suite_create("Table");

    TCase * t = tcase_create("Core");
    tcase_add_test(t, first_conflict_error);
    tcase_add_test(t, follow_conflict_error);
    suite_add_tcase(s, t);

    return s;
}
