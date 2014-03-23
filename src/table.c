#include <stdlib.h>
#include <stdio.h>
#include <libooc/hash.h>
#include <libooc/array.h>

#include "token.h"
#include "nonterminal.h"
#include "table.struct.h"

def_class(Table, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->nonterminals = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

// NT set init

def(NT_set_init_iter, void : void * @nonterminal . size_t @index) {
    void * token = Nonterminal_token(nonterminal);
    Hash_set(self->nonterminal_set, token, nonterminal);
}

def(NT_set_init, void) {
    self->nonterminal_set = new(Hash);
    Array_each(self->nonterminals, Table_NT_set_init_iter, self);
}

// T set init

def(T_set_init_token_iter, void : void * @token . size_t @index) {
    if(Hash_get(self->nonterminal_set, token) == NULL &&
            strcmp(inspect(token), "epsilon") != 0) {
        Hash_set(self->terminal_set, token, token);
    }
}

def(T_set_init_stmt_iter, void : void * @stmt . size_t @index) {
    Array_each(stmt, Table_T_set_init_token_iter, self);
}

def(T_set_init_iter, void : void * @nonterminal . size_t @index) {
    void * stmts = Nonterminal_stmts(nonterminal);
    Array_each(stmts, Table_T_set_init_stmt_iter, self);
}

def(T_set_init, void) {
    self->terminal_set = new(Hash);
    Array_each(self->nonterminals, Table_T_set_init_iter, self);
}

// build Ts

def(Ts_init_iter, void : void * @terminal . void * @data) {
    Array_push(self->terminals, terminal);
}

def(Ts_init, void) {
    self->terminals = new(Array);
    Hash_each(self->terminal_set, Table_Ts_init_iter, self);
}

static void
terminals_iter(void * null, void * terminal, size_t index) {
    printf("terminal: %s\n", inspect(terminal));
}

// null ?

struct self_with_NT {
    struct Table * self;
    void * nonterminal;
};

static bool
token_present_p(void * _args, void * token, size_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = Hash_get(args->self->nonterminal_set, token);
    void * terminal = Hash_get(args->self->terminal_set, token);
    if(nonterminal != NULL && nonterminal != args->nonterminal) {
        printf("NT[%s]\n", inspect(token));
        null_init_NT(args->self, nonterminal);
        enum NT_TYPE type = Nonterminal_type(nonterminal);
        if(type == PRESENT) {
            return true;
        }
    } else if(terminal != NULL) {
        printf("T[%s]\n", inspect(token));
        return true;
    } else {
        printf("%s\n", inspect(token));
    }
    return false;
}

static bool
stmt_blank_p(void * args, void * stmt, size_t index) {
    return !Array_any_p(stmt, token_present_p, args);
}

def(null_init_NT, void : void * @nonterminal) {
    enum NT_TYPE type = Nonterminal_type(nonterminal);
    if(type == NOT_SET) {
        void * stmts = Nonterminal_stmts(nonterminal);
        struct self_with_NT args;
        args.self = self;
        args.nonterminal = nonterminal;
        enum NT_TYPE nt_type = Array_any_p(stmts, stmt_blank_p, &args) ? BLANK : PRESENT;
        Nonterminal_set_type(nonterminal, nt_type);
        printf("--- %s %s ---\n",
                inspect(Nonterminal_token(nonterminal)),
                nt_type == PRESENT ? "T" : "F");
    }
}

def(null_init_iter, void : void * @nonterminal . size_t @index) {
    null_init_NT(self, nonterminal);
}

def(null_init, void) {
    Array_each(self->nonterminals, Table_null_init_iter, self);
}

static bool
first_token_iter(void * _args, void * token, size_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = Hash_get(args->self->nonterminal_set, token);
    void * terminal = Hash_get(args->self->terminal_set, token);
    if(nonterminal != NULL) {
        void * subset = Nonterminal_subset(args->nonterminal);
        Hash_set(subset, nonterminal, nonterminal);
        return Nonterminal_type(nonterminal) == PRESENT;
    } else if(terminal != NULL) {
        void * first = Nonterminal_first(args->nonterminal);
        Hash_set(first, token, token);
        return true;
    } else {
        return false;
    }
}

static void
first_stmt_iter(void * args, void * stmt, size_t index) {
    Array_any_p(stmt, first_token_iter, args);
}

def(first_init_NT, void : void * @nonterminal) {
    void * stmts = Nonterminal_stmts(nonterminal);
    struct self_with_NT args;
    args.self = self;
    args.nonterminal = nonterminal;
    Array_each(stmts, first_stmt_iter, &args);
}

static void
traverse_add(void * ancestor, void * nonterminal, void * data) {
    void * union_set = Nonterminal_union_set(ancestor);
    Hash_set(union_set, nonterminal, nonterminal);
    void * traversed = Nonterminal_traversed(nonterminal);
    Hash_set(traversed, ancestor, ancestor);
}

static void
traverse(void * nonterminal, void * ancestor);

static void
traverse_iter(void * ancestor, void * nonterminal, void * data) {
    traverse(nonterminal, ancestor);
}

static void
traverse(void * nonterminal, void * ancestor) {
    printf("ancestor[%s] NT[%s]\n",
            inspect(Nonterminal_token(ancestor)),
            inspect(Nonterminal_token(nonterminal)));
    if(!Nonterminal_traversed_by_p(nonterminal, ancestor)) {
        if(Nonterminal_done_p(nonterminal)) {
            void * union_set = Nonterminal_union_set(nonterminal);
            Hash_each(union_set, traverse_add, ancestor);
        } else {
            traverse_add(ancestor, nonterminal, nonterminal);
            void * subset = Nonterminal_subset(nonterminal);
            Hash_each(subset, traverse_iter, ancestor);
        }
    }
    printf("ancestor[%s] ---\n",
            inspect(Nonterminal_token(ancestor)));
}

static void
first_iter(void * nonterminal, void * token, void * data) {
    printf("first[%s]: %s\n",
            inspect(Nonterminal_token(nonterminal)),
            inspect(token));
}

static void
subset_iter(void * nonterminal, void * token, void * data) {
    printf("subset[%s]: %s\n",
            inspect(Nonterminal_token(nonterminal)),
            inspect(Nonterminal_token(token)));
}

def(first_init_NTs, void : void * @nonterminal . size_t @index) {
    Nonterminal_first_init(nonterminal);
    first_init_NT(self, nonterminal);
    void * first = Nonterminal_first(nonterminal);
    Hash_each(first, first_iter, nonterminal);
    void * subset = Nonterminal_subset(nonterminal);
    Hash_each(subset, subset_iter, nonterminal);
}

static void
union_set_iter(void * nonterminal, void * token, void * data) {
    printf("               %s\n",
            inspect(Nonterminal_token(token)));
}

def(first_init_traverse, void : void * @nonterminal . size_t @index) {
    traverse(nonterminal, nonterminal);
    Nonterminal_set_done(nonterminal, true);
    void * union_set = Nonterminal_union_set(nonterminal);
    Hash_each(union_set, union_set_iter, nonterminal);
}

def(first_init, void) {
    Array_each(self->nonterminals, Table_first_init_NTs, self);
    Array_each(self->nonterminals, Table_first_init_traverse, self);
}

def(build, void *) {
    NT_set_init(self);
    T_set_init(self);
    Ts_init(self);
    Array_each(self->terminals, terminals_iter, NULL);
    null_init(self);
    first_init(self);
    return NULL;
}
