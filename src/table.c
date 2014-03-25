#include <stdlib.h>
#include <stdio.h>
#include <libooc/hash.h>
#include <libooc/array.h>

#include "token.h"
#include "nonterminal.h"
#include "production.h"
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

// NT set

def(NT_set_each_NT, void : void * @nonterminal . size_t @index) {
    void * token = Nonterminal_token(nonterminal);
    Hash_set(self->nonterminal_set, token, nonterminal);
}

private
def(NT_set_init, void) {
    self->nonterminal_set = new(Hash);
    Array_each(self->nonterminals, Table_NT_set_each_NT, self);
}

// T set

def(T_set_each_token, void : void * @token . size_t @index) {
    if(Hash_get(self->nonterminal_set, token) == NULL &&
            strcmp(inspect(token), "epsilon") != 0) {
        Hash_set(self->terminal_set, token, token);
    }
}

def(T_set_each_prod, void : void * @production . size_t @index) {
    void * tokens = Production_tokens(production);
    Array_each(tokens, Table_T_set_each_token, self);
}

def(T_set_each_NT, void : void * @nonterminal . size_t @index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, Table_T_set_each_prod, self);
}

private
def(T_set_init, void) {
    self->terminal_set = new(Hash);
    Array_each(self->nonterminals, Table_T_set_each_NT, self);
}

// Ts

def(Ts_each_T, void : void * @terminal . void * @data) {
    Array_push(self->terminals, terminal);
}

private
def(Ts_init, void) {
    self->terminals = new(Array);
    Hash_each(self->terminal_set, Table_Ts_each_T, self);
}

// null ?

struct self_with_NT {
    struct Table * self;
    void * nonterminal;
    void * production;
};

static bool
token_present_p(void * _args, void * token, size_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = Hash_get(args->self->nonterminal_set, token);
    void * terminal = Hash_get(args->self->terminal_set, token);
    if(nonterminal != NULL && nonterminal != args->nonterminal) {
        printf("NT[%s]\n", inspect(token));
        null_NT(args->self, nonterminal);
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
prod_blank_p(void * args, void * production, size_t index) {
    void * tokens = Production_tokens(production);
    bool present = Array_any_p(tokens, token_present_p, args);
    Production_set_type(production, present ? PRESENT : BLANK);
    return !present;
}

def(null_NT, void : void * @nonterminal) {
    enum NT_TYPE type = Nonterminal_type(nonterminal);
    if(type == NOT_SET) {
        void * productions = Nonterminal_productions(nonterminal);
        struct self_with_NT args;
        args.self = self;
        args.nonterminal = nonterminal;
        enum NT_TYPE nt_type = Array_any_p(productions, prod_blank_p, &args) ? BLANK : PRESENT;
        Nonterminal_set_type(nonterminal, nt_type);
        printf("--- %s %s ---\n",
                inspect(Nonterminal_token(nonterminal)),
                nt_type == PRESENT ? "T" : "F");
    }
}

def(null_each_NT, void : void * @nonterminal . size_t @index) {
    null_NT(self, nonterminal);
}

private
def(null_init, void) {
    Array_each(self->nonterminals, Table_null_each_NT, self);
}

// traverse algorithm

static void
traverse_add_each_prod(void * ancestor, void * production, size_t index) {
    void * union_set = Production_union_set(ancestor);
    Hash_set(union_set, production, production);
    void * traversed = Production_traversed(production);
    Hash_set(traversed, ancestor, ancestor);
}

static void
traverse_add_each_NT(void * ancestor, void * production, void * data) {
    void * union_set = Production_union_set(ancestor);
    Hash_set(union_set, production, production);
}

static void
traverse(void * nonterminal, void * ancestor);

static void
traverse_each_prod(void * ancestor, void * production, size_t index) {
    traverse(production, ancestor);
}

static void
traverse_each_NT(void * ancestor, void * nonterminal, void * data) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, traverse_each_prod, ancestor);
}

static void
traverse(void * production, void * ancestor) {
    printf("ancestor[%s][%zd] P[%s][%zd]\n",
            inspect(ancestor),
            Production_no(ancestor),
            inspect(production),
            Production_no(production));
    if(!Production_traversed_by_p(production, ancestor)) {
        if(Production_done_p(production)) {
            void * union_set = Production_union_set(production);
            Hash_each(union_set, traverse_add_each_NT, ancestor);
        } else {
            traverse_add_each_prod(ancestor, production, 0);
            void * subset = Production_subset(production);
            Hash_each(subset, traverse_each_NT, ancestor);
        }
    }
    printf("ancestor[%s][%zd] ---\n",
            inspect(ancestor),
            Production_no(ancestor));
}

// first

// first subset

static bool
first_subset_each_token(void * _args, void * token, size_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = Hash_get(args->self->nonterminal_set, token);
    void * terminal = Hash_get(args->self->terminal_set, token);
    if(nonterminal != NULL) {
        void * subset = Production_subset(args->production);
        Hash_set(subset, nonterminal, nonterminal);
        return Nonterminal_type(nonterminal) == PRESENT;
    } else if(terminal != NULL) {
        void * first = Production_first(args->production);
        Hash_set(first, terminal, terminal);
        return true;
    } else {
        return false;
    }
}

static void
first_subset_each_prod(void * _args, void * production, size_t index) {
    Production_first_init(production);
    struct self_with_NT * args = _args;
    args->production = production;
    void * tokens = Production_tokens(production);
    Array_any_p(tokens, first_subset_each_token, args);
}

static void
first_subset_each_NT(void * self, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    struct self_with_NT args;
    args.self = self;
    args.nonterminal = nonterminal;
    Array_each(productions, first_subset_each_prod, &args);
}

// first traverse

static void
first_traverse_each_prod(void * null, void * production, size_t index) {
    traverse(production, production);
    Production_set_done(production, true);
}

static void
first_traverse_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, first_traverse_each_prod, NULL);
}

// first union

static void
first_union_each_token(void * ancestor, void * token, void * data) {
    void * first = Production_first(ancestor);
    Hash_set(first, token, token);
}

static void
first_union_each_prod2(void * ancestor, void * production, void * data) {
    void * first = Production_first(production);
    Hash_each(first, first_union_each_token, ancestor);
}

static void
first_union_each_prod(void * null, void * production, size_t index) {
    void * union_set = Production_union_set(production);
    Hash_each(union_set, first_union_each_prod2, production);
}

static void
first_union_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, first_union_each_prod, NULL);
}

// debug: terminals

static void
debug_Ts_each_T(void * null, void * terminal, size_t index) {
    printf("T: %s\n", inspect(terminal));
}

def(debug_Ts, void) {
    Array_each(self->terminals, debug_Ts_each_T, NULL);
}

// debug: first

static void
debug_first_each_token(void * production, void * token, void * data) {
    printf("first[%s][%zd][%s]: %s\n",
            inspect(production),
            Production_no(production),
            Production_type(production) == PRESENT ? "T" : (
                Production_type(production) == BLANK ? "F" : "?"),
            inspect(token));
}

static void
debug_first_each_prod(void * null, void * production, size_t index) {
    void * first = Production_first(production);
    Hash_each(first, debug_first_each_token, production);
}

static void
debug_first_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, debug_first_each_prod, NULL);
}

// debug: subset

static void
debug_subset_each_token(void * production, void * token, void * data) {
    printf("subset[%s][%zd](%p): %s\n",
            inspect(production),
            Production_no(production),
            production,
            inspect(Nonterminal_token(token)));
}

static void
debug_subset_each_prod(void * null, void * production, size_t index) {
    void * subset = Production_subset(production);
    Hash_each(subset, debug_subset_each_token, production);
}

static void
debug_subset_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, debug_subset_each_prod, NULL);
}

// debug: union

static void
debug_union_each_token(void * production, void * token, void * data) {
    printf("union[%s][%zd]: [%s][%zd]\n",
            inspect(production),
            Production_no(production),
            inspect(token),
            Production_no(token));
}

static void
debug_union_each_prod(void * null, void * production, size_t index) {
    void * union_set = Production_union_set(production);
    Hash_each(union_set, debug_union_each_token, production);
}

static void
debug_union_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, debug_union_each_prod, NULL);
}

// debug: follow

static void
debug_follow_each_token(void * production, void * token, void * data) {
    printf("follow[%s][%zd][%s]: %s\n",
            inspect(production),
            Production_no(production),
            Production_type(production) == PRESENT ? " " : (
                Production_type(production) == BLANK ? "F" : "?"),
            inspect(token));
}

static void
debug_follow_each_prod(void * null, void * production, size_t index) {
    void * follow = Production_follow(production);
    Hash_each(follow, debug_follow_each_token, production);
}

static void
debug_follow_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, debug_follow_each_prod, NULL);
}

private
def(first_init, void) {
    Array_each(self->nonterminals, first_subset_each_NT, self);
    Array_each(self->nonterminals, debug_first_each_NT, self);
    Array_each(self->nonterminals, first_traverse_each_NT, self);
    Array_each(self->nonterminals, first_union_each_NT, self);
    Array_each(self->nonterminals, debug_union_each_NT, self);
    Array_each(self->nonterminals, debug_first_each_NT, self);
}

// follow

static void
follow_each_prod(void * null, void * production, size_t index) {
    Production_follow_init(production);
    Production_set_done(production, false);
}

static void
follow_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, follow_each_prod, NULL);
}

static void
follow_append_each_prod(void * next_nonterminal, void * production, size_t index) {
    void * subset = Production_subset(production);
    Hash_set(subset, next_nonterminal, next_nonterminal);
    printf("  (%s)[%zd] << NT:follow[%s]\n",
            inspect(production),
            Production_no(production),
            inspect(Nonterminal_token(next_nonterminal)));
}

static void
follow_append_first_each_prod2(void * token, void * production, size_t index) {
    void * follow = Production_follow(production);
    Hash_set(follow, token, token);
    printf("  (%s)[%zd] << T:first[%s]\n",
            inspect(production),
            Production_no(production),
            inspect(token));
}

static void
follow_append_first_each_NT(void * nonterminal, void * token, void * data) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, follow_append_first_each_prod2, token);
}

static void
follow_append_first_each_prod(void * nonterminal, void * production, size_t index) {
    void * first = Production_first(production);
    Hash_each(first, follow_append_first_each_NT, nonterminal);
}

static void
follow_append_T_each_prod(void * next_terminal, void * production, size_t index) {
    void * follow = Production_follow(production);
    Hash_set(follow, next_terminal, next_terminal);
    printf("  (%s)[%zd] << T[%s]\n",
            inspect(production),
            Production_no(production),
            inspect(next_terminal));
}

static void
follow_append_NT_each_prod(void * nonterminal, void * production, size_t index) {
    void * subset = Production_subset(production);
    Hash_set(subset, nonterminal, nonterminal);
    printf("  (%s)[%zd] << NT[%s]\n",
            inspect(production),
            Production_no(production),
            inspect(Nonterminal_token(nonterminal)));
}

static void
follow_subset_each_token(void * _args, void * token, size_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = Hash_get(args->self->nonterminal_set, token);
    if(nonterminal == NULL) {
        return;
    }
    printf("  (%s)\n",
            inspect(Nonterminal_token(nonterminal)));
    void * tokens = Production_tokens(args->production);
    size_t len = Array_len(tokens);
    index += 1;
    while(index < len) {
        void * next_token = Array_get(tokens, index);
        void * next_nonterminal = Hash_get(args->self->nonterminal_set, next_token);
        void * next_terminal = Hash_get(args->self->terminal_set, next_token);
        if(next_nonterminal != NULL) {
            void * productions = Nonterminal_productions(nonterminal);
            Array_each(productions, follow_append_each_prod, next_nonterminal);
            productions = Nonterminal_productions(next_nonterminal);
            Array_each(productions, follow_append_first_each_prod, nonterminal);
            enum NT_TYPE type = Nonterminal_type(next_nonterminal);
            if(type == PRESENT) {
                break;
            }
        } else if(next_terminal != NULL) {
            void * productions = Nonterminal_productions(nonterminal);
            Array_each(productions, follow_append_T_each_prod, next_terminal);
            return;
        }
        index += 1;
    }
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, follow_append_NT_each_prod, args->nonterminal);
}

static void
follow_subset_each_prod(void * _args, void * production, size_t index) {
    struct self_with_NT * args = _args;
    args->production = production;
    void * tokens = Production_tokens(production);
    Array_each(tokens, follow_subset_each_token, args);
}

static void
follow_subset_each_NT(void * self, void * nonterminal, size_t index) {
    printf("[%s]\n",
            inspect(Nonterminal_token(nonterminal)));
    void * productions = Nonterminal_productions(nonterminal);
    struct self_with_NT args;
    args.self = self;
    args.nonterminal = nonterminal;
    Array_each(productions, follow_subset_each_prod, &args);
}

static void
follow_union_each_token(void * ancestor, void * token, void * data) {
    void * follow = Production_follow(ancestor);
    Hash_set(follow, token, token);
}

static void
follow_union_each_NT2(void * ancestor, void * production, void * data) {
    void * follow = Production_follow(production);
    Hash_each(follow, follow_union_each_token, ancestor);
}

static void
follow_union_each_prod(void * null, void * production, size_t index) {
    void * union_set = Production_union_set(production);
    Hash_each(union_set, follow_union_each_NT2, production);
}

static void
follow_union_each_NT(void * null, void * nonterminal, size_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, follow_union_each_prod, NULL);
}

private
def(follow_init, void) {
    Array_each(self->nonterminals, follow_each_NT, self);
    Array_each(self->nonterminals, follow_subset_each_NT, self);
    Array_each(self->nonterminals, debug_follow_each_NT, self);
    Array_each(self->nonterminals, debug_subset_each_NT, self);
    Array_each(self->nonterminals, first_traverse_each_NT, self);
    Array_each(self->nonterminals, debug_union_each_NT, self);
    Array_each(self->nonterminals, follow_union_each_NT, self);
    Array_each(self->nonterminals, debug_follow_each_NT, self);
    Array_each(self->nonterminals, debug_first_each_NT, self);
}

def(build, void *) {
    NT_set_init(self);
    T_set_init(self);
    Ts_init(self);
    debug_Ts(self);
    null_init(self);
    first_init(self);
    follow_init(self);
    return NULL;
}
