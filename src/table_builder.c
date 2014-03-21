#include <stdlib.h>
#include <stdio.h>
#include <libooc/hash.h>
#include <libooc/array.h>

#include "token.h"
#include "nonterminal.struct.h"
#include "table_builder.struct.h"

struct Sets {
    void * nonterminal_set;
    void * terminal_set;
};

def_class(TableBuilder, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->nonterminals = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

static void
build_nonterminal_set_iter(void * nonterminal_set, void * nonterminal, size_t index) {
    void * token = Nonterminal_token(nonterminal);
    Hash_set(nonterminal_set, token, token);
}

private
def(build_nonterminal_set, void : struct Sets * @sets) {
    Array_each(self->nonterminals, sets->nonterminal_set, build_nonterminal_set_iter);
}

static void
build_terminal_set_token_iter(void * _sets, void * token, size_t index) {
    struct Sets * sets = _sets;
    if(Hash_get(sets->nonterminal_set, token) == NULL) {
        Hash_set(sets->terminal_set, token, token);
    }
}

static void
build_terminal_set_stmt_iter(void * sets, void * stmt, size_t index) {
    Array_each(stmt, sets, build_terminal_set_token_iter);
}

static void
build_terminal_set_iter(void * sets, void * nonterminal, size_t index) {
    void * stmts = Nonterminal_stmts(nonterminal);
    Array_each(stmts, sets, build_terminal_set_stmt_iter);
}

private
def(build_terminal_set, void : struct Sets * @sets) {
    Array_each(self->nonterminals, sets, build_terminal_set_iter);
}

static void
build_terminals_iter(void * terminal_set, void * terminal, void * data) {
    Array_push(terminal_set, terminal);
}

private
def(build_terminals, void) {
    struct Sets sets;
    sets.nonterminal_set = new(Hash);
    sets.terminal_set = new(Hash);
    build_nonterminal_set(self, &sets);
    build_terminal_set(self, &sets);
    self->terminals = new(Array);
    Hash_each(sets.terminal_set, self->terminals, build_terminals_iter);
    free(sets.nonterminal_set);
    free(sets.terminal_set);
}

static void
terminals_iter(void * null, void * terminal, size_t index) {
    printf("terminal: %s\n", inspect(terminal));
}

def(build, void *) {
    build_terminals(self);
    Array_each(self->terminals, NULL, terminals_iter);
    return NULL;
}
