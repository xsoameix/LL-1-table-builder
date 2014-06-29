lib_LIBRARIES = libll1.a
libll1_a_SOURCES =  \
    ll1.c           \
    token.c         \
    scanner.c       \
    parser.c        \
    nonterminal.c   \
    terminal.c      \
    block.c         \
    production.c    \
    table.c
libll1_a_CFLAGS = $(DEPS_CFLAGS)

bin_PROGRAMS = ll1
ll1_SOURCES = main.c
ll1_LDADD = $(top_builddir)/src/libll1.a $(DEPS_LIBS)
