TESTS = check_ll1
check_PROGRAMS = check_ll1
check_ll1_SOURCES = \
    ll1.c   \
    table.c
check_ll1_CFLAGS = $(DEPS_CFLAGS) @CHECK_CFLAGS@ 
check_ll1_LDADD = $(top_builddir)/src/libll1.a $(DEPS_LIBS) @CHECK_LIBS@
