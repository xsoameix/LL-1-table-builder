#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libooc/hash.h>
#include <libooc/array.h>
#include <libooc/file.h>
#include <libooc/inttype.h>

#include "token.h"
#include "terminal.h"
#include "nonterminal.h"
#include "production.h"
#include "block.h"
#include "table.struct.h"

O_DEF_CLASS(Table, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->nonterminals = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

// NT set

private
def(NT_set_init, void) {

    void each_NT(void * _self, void * nonterminal, uint_t index) {
        struct Table * self = _self;
        void * token = Nonterminal_token(nonterminal);
        Hash_set(self->nonterminal_set, token, nonterminal);
    }

    self->nonterminal_set = new(Hash);
    Array_each(self->nonterminals, each_NT, self);
}

private
def(NT_p, bool : void * @token) {
    return Hash_get(self->nonterminal_set, token) != NULL;
}

private
def(NT_of_token, void * : void * @token) {
    return Hash_get(self->nonterminal_set, token);
}

// production epsilon

private
def(production_epsilon, void) {

    void each_prod(void * _self, void * production, uint_t index) {
        struct Table * self = _self;
        void * tokens = Production_tokens(production);
        if(Array_len(tokens) == 1) {
            void * token = Array_get(tokens, 0);
            if(!NT_p(self, token) && strcmp(inspect(token), "epsilon") == 0) {
                Production_set_epsilon(production, true);
            }
        }
    }

    void each_NT(void * self, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, self);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// T set

private
def(T_set_init, void) {

    void each_token(void * _self, void * token, uint_t index) {
        struct Table * self = _self;
        if(!NT_p(self, token)) {
            void * terminal = new(Terminal, token);
            Hash_set(self->terminal_set, token, terminal);
        }
    }

    void each_prod(void * self, void * production, uint_t index) {
        if(!Production_epsilon(production)) {
            void * tokens = Production_tokens(production);
            Array_each(tokens, each_token, self);
        }
    }

    void each_NT(void * self, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, self);
    }

    self->terminal_set = new(Hash);
    Array_each(self->nonterminals, each_NT, self);
}

private
def(T_p, bool : void * @token) {
    return Hash_get(self->terminal_set, token) != NULL;
}

private
def(T_of_token, void * : void * @token) {
    return Hash_get(self->terminal_set, token);
}

// Ts

private
def(Ts_init, void) {

    void each_T(void * _self, void * token, void * terminal) {
        struct Table * self = _self;
        Array_push(self->terminals, terminal);
    }

    self->terminals = new(Array);
    Hash_each(self->terminal_set, each_T, self);
}

// null ?

struct self_with_NT {
    struct Table * self;
    void * nonterminal;
    void * production;
};

static bool
token_present_p(void * _args, void * token, uint_t index) {
    struct self_with_NT * args = _args;
    void * nonterminal = NT_of_token(args->self, token);
    void * terminal    =  T_of_token(args->self, token);
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
prod_blank_p(void * args, void * production, uint_t index) {
    void * tokens = Production_tokens(production);
    bool present = Array_any_p(tokens, token_present_p, args);
    Production_set_type(production, present ? PRESENT : BLANK);
    return !present;
}

private
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

private
def(null_init, void) {

    void each_NT(void * self, void * nonterminal, uint_t index) {
        null_NT(self, nonterminal);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// traverse algorithm

static void
traverse(void * production, void * ancestor) {

    // traverse_add NT, prod

    void add_prod_to_ancestor(void * ancestor, void * production, void * unused) {
        void * union_set = Production_union_set(ancestor);
        Hash_set(union_set, production, production);
    }

    void add_ancestor_to_prod(void * ancestor, void * production) {
        void * traversed = Production_traversed(production);
        Hash_set(traversed, ancestor, ancestor);
    }

    // traverse NT, prod

    void each_prod(void * ancestor, void * production, uint_t index) {
        traverse(production, ancestor);
    }

    void each_NT(void * ancestor, void * nonterminal, void * data) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, ancestor);
    }

    printf("ancestor[%s][%zu] P[%s][%zu]\n",
            inspect(ancestor),
            Production_no(ancestor),
            inspect(production),
            Production_no(production));
    if(!Production_traversed_by_p(production, ancestor)) {
        if(Production_done_p(production)) {
            void * union_set = Production_union_set(production);
            Hash_each(union_set, add_prod_to_ancestor, ancestor);
        } else {
            add_prod_to_ancestor(ancestor, production, 0);
            add_ancestor_to_prod(ancestor, production);
            void * subset = Production_subset(production);
            Hash_each(subset, each_NT, ancestor);
        }
    }
    printf("ancestor[%s][%zu] ---\n",
            inspect(ancestor),
            Production_no(ancestor));
}

// first

// set first{terminals} & subset{nonterminals}

private
def(first_subset_init, void) {

    bool each_token(void * _args, void * token, uint_t index) {
        struct self_with_NT * args = _args;
        void * nonterminal = NT_of_token(args->self, token);
        void * terminal    =  T_of_token(args->self, token);
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

    void each_prod(void * _args, void * production, uint_t index) {
        Production_first_init(production);
        struct self_with_NT * args = _args;
        args->production = production;
        void * tokens = Production_tokens(production);
        Array_any_p(tokens, each_token, args);
    }

    void each_NT(void * self, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        struct self_with_NT args;
        args.self = self;
        args.nonterminal = nonterminal;
        Array_each(productions, each_prod, &args);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// set union_set{productions}

private
def(traverse_NTs, void) {

    void each_prod(void * unused, void * production, uint_t index) {
        traverse(production, production);
        Production_set_done(production, true);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// set first{terminals} by union_set{productions}
//
// first_each_NT
//   [A] ->  B
//
// first_each_prod
//    A  -> [B]

private
def(first_init_after_traverse, void) {

    void each_T(void * ancestor, void * terminal, void * data) {
        void * first = Production_first(ancestor);
        Hash_set(first, terminal, terminal);
    }

    void each_prod2(void * ancestor, void * production, void * data) {
        void * first = Production_first(production);
        Hash_each(first, each_T, ancestor);
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * union_set = Production_union_set(production);
        Hash_each(union_set, each_prod2, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// debug: terminals

private
def(debug_Ts, void) {

    void each_T(void * unused, void * terminal, uint_t index) {
        printf("T: %s\n", inspect(terminal));
    }

    Array_each(self->terminals, each_T, NULL);
}

// debug: first{terminals}

private
def(debug_first, void) {

    void each_T(void * production, void * terminal, void * data) {
        printf("first[%s][%zu][%s]: %s\n",
                inspect(production),
                Production_no(production),
                Production_type(production) == PRESENT ? "T" : (
                    Production_type(production) == BLANK ? "F" : "?"),
                inspect(terminal));
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * first = Production_first(production);
        Hash_each(first, each_T, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// debug: subset{nonterminals}

private
def(debug_subset, void) {

    void each_token(void * production, void * token, void * data) {
        printf("subset[%s][%zu](%p): %s\n",
                inspect(production),
                Production_no(production),
                production,
                inspect(Nonterminal_token(token)));
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * subset = Production_subset(production);
        Hash_each(subset, each_token, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// debug: union{productions}

private
def(debug_union, void) {

    void each_token(void * production, void * token, void * data) {
        printf("union[%s][%zu]: [%s][%zu]\n",
                inspect(production),
                Production_no(production),
                inspect(token),
                Production_no(token));
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * union_set = Production_union_set(production);
        Hash_each(union_set, each_token, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// debug: follow{terminals}

private
def(debug_follow, void) {

    void each_T(void * production, void * terminal, void * data) {
        printf("follow[%s][%zu][%s]: %s\n",
                inspect(production),
                Production_no(production),
                Production_type(production) == PRESENT ? " " : (
                    Production_type(production) == BLANK ? "F" : "?"),
                inspect(terminal));
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * follow = Production_follow(production);
        Hash_each(follow, each_T, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

private
def(first_init, void) {
    first_subset_init(self);
    debug_first(self);
    traverse_NTs(self);
    first_init_after_traverse(self);
    debug_union(self);
    debug_first(self);
}

// follow

// init follow{terminals}

private
def(follow_Ts_init, void) {

    void each_prod(void * unused, void * production, uint_t index) {
        Production_follow_init(production);
        Production_set_done(production, false);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

private
def(follow_subset_init, void) {

    // merge next nonterminal into subset{nonterminals}

    void add_next_NT_to_subset(void * next_nonterminal, void * production, uint_t index) {
        void * subset = Production_subset(production);
        Hash_set(subset, next_nonterminal, next_nonterminal);
        printf("  (%s)[%zu] << NT[%s]\n",
                inspect(production),
                Production_no(production),
                inspect(Nonterminal_token(next_nonterminal)));
    }

    // merge first{terminals} of next nonterminal into follow{terminals}

    void add_first_of_next_NT_to_follow(void * nonterminal, void * production, uint_t index) {

        void each_prod(void * terminal, void * production, uint_t index) {
            void * follow = Production_follow(production);
            Hash_set(follow, terminal, terminal);
            printf("  (%s)[%zu] << T:first[%s]\n",
                    inspect(production),
                    Production_no(production),
                    inspect(terminal));
        }

        void each_NT(void * nonterminal, void * terminal, void * data) {
            void * productions = Nonterminal_productions(nonterminal);
            Array_each(productions, each_prod, terminal);
        }

        void * first = Production_first(production);
        Hash_each(first, each_NT, nonterminal);
    }

    // merge next terminal into follow{terminals}

    void add_next_T_to_follow(void * next_terminal, void * production, uint_t index) {
        void * follow = Production_follow(production);
        Hash_set(follow, next_terminal, next_terminal);
        printf("  (%s)[%zu] << T[%s]\n",
                inspect(production),
                Production_no(production),
                inspect(next_terminal));
    }

    // merge the nonterminal on the left hand side into subset{nonterminals}

    void add_LHS_NT_to_subset(void * nonterminal, void * production, uint_t index) {
        void * subset = Production_subset(production);
        Hash_set(subset, nonterminal, nonterminal);
        printf("  (%s)[%zu] << NT:LHS[%s]\n",
                inspect(production),
                Production_no(production),
                inspect(Nonterminal_token(nonterminal)));
    }

    // set follow{terminals} & subset{nonterminals}

    void each_token(void * _args, void * token, uint_t index) {
        struct self_with_NT * args = _args;
        void * nonterminal = NT_of_token(args->self, token);
        if(nonterminal == NULL) {
            return;
        }
        printf("  (%s)\n",
                inspect(Nonterminal_token(nonterminal)));
        void * tokens = Production_tokens(args->production);
        uint_t len = Array_len(tokens);
        index += 1;
        while(index < len) {
            void * next_token = Array_get(tokens, index);
            void * next_nonterminal = NT_of_token(args->self, next_token);
            void * next_terminal    =  T_of_token(args->self, next_token);
            if(next_nonterminal != NULL) {
                // merge next nonterminal into subset{nonterminals}
                void * productions = Nonterminal_productions(nonterminal);
                Array_each(productions, add_next_NT_to_subset, next_nonterminal);

                // merge first{terminals} of next nonterminal into follow{terminals}
                productions = Nonterminal_productions(next_nonterminal);
                Array_each(productions, add_first_of_next_NT_to_follow, nonterminal);
                enum NT_TYPE type = Nonterminal_type(next_nonterminal);
                if(type == PRESENT) {
                    return;
                }
            } else if(next_terminal != NULL) {
                // merge next terminal into follow{terminals}
                void * productions = Nonterminal_productions(nonterminal);
                Array_each(productions, add_next_T_to_follow, next_terminal);
                return;
            }
            index += 1;
        }
        // merge the nonterminal on the left hand side into subset{nonterminals}
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, add_LHS_NT_to_subset, args->nonterminal);
    }

    void each_prod(void * _args, void * production, uint_t index) {
        struct self_with_NT * args = _args;
        args->production = production;
        void * tokens = Production_tokens(production);
        Array_each(tokens, each_token, args);
    }

    void each_NT(void * self, void * nonterminal, uint_t index) {
        printf("[%s]\n",
                inspect(Nonterminal_token(nonterminal)));
        void * productions = Nonterminal_productions(nonterminal);
        struct self_with_NT args;
        args.self = self;
        args.nonterminal = nonterminal;
        Array_each(productions, each_prod, &args);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// set follow{terminals} by union_set{productions}
//
// follow_each_NT
//   [A] ->  B
//
// follow_each_prod
//    A  -> [B]

private
def(follow_init_after_traverse, void) {

    void each_T(void * ancestor, void * terminal, void * data) {
        void * follow = Production_follow(ancestor);
        Hash_set(follow, terminal, terminal);
    }

    void each_prod2(void * ancestor, void * production, void * data) {
        void * follow = Production_follow(production);
        Hash_each(follow, each_T, ancestor);
    }

    void each_prod(void * unused, void * production, uint_t index) {
        void * union_set = Production_union_set(production);
        Hash_each(union_set, each_prod2, production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

// follow clear set: subset, union_set, traversed

private
def(follow_clear_set, void) {

    void each_prod(void * unused, void * production, uint_t index) {
        Production_clear_set(production);
    }

    void each_NT(void * unused, void * nonterminal, uint_t index) {
        void * productions = Nonterminal_productions(nonterminal);
        Array_each(productions, each_prod, NULL);
    }

    Array_each(self->nonterminals, each_NT, self);
}

private
def(follow_init, void) {
    follow_Ts_init(self);
    follow_subset_init(self);
    debug_follow(self);
    debug_subset(self);
    traverse_NTs(self);
    debug_union(self);
    follow_init_after_traverse(self);
    follow_clear_set(self);
    debug_follow(self);
    debug_first(self);
}

//          +                         *                           (                      )               digit
// 0 expr                                                         {10}term{11}expr'{12}                  {10}term{11}expr'{12}
// 1 expr'  {13}+{14}term{15}expr'{16}                                                   {17}epsilon{18}
// 2 term                                                         {19}factor{20}term'{21}                {19}factor{20}term'{21}
// 3 term'  {26}epsilon{27}           {22}*{23}factor{24}term'{25}                       {26}epsilon{27}
// 4 factor                                                       {28}({29}expr{30}){31}                 {32}digit{33}
// 5 +
// 6 *
// 7 (
// 8 )
// 9 digit
// 10 {}digit
// 11 digit{ $$ = $1 }
// 
// 0 expr -> term expr'
// 1 expr' -> + term expr'
// 2          | epsilon
// 3 term -> factor term'
// 4 term' -> * factor term'
// 5          | epsilon
// 6 factor -> ( expr )
// 7           | digit
// 
// static int act[5][5] = {
//     {-1, -1,  0, -1,  0},
//     { 1, -1, -1,  2, -1},
//     {-1, -1,  3, -1,  3},
//     { 5,  4, -1,  5, -1},
//     {-1, -1,  6, -1,  7}
// };
// 
// static int prhs[] = {
//     0,
//     3,
//     6,
//     7,
//     10,
//     13,
//     14,
//     18
// };
// 
// static int rhs[] = {
//     2, 1, -1,
//     5, 2, 1, -1,
//     4, 3, -1,
//     6, 4, 3, -1,
//     7, 0, 8, -1,
//     10, 9, 11, -1
// };
// 
// static void
// driver(void) {
//     void * vs = new(Array); // value stack
//     void * as = new(Array); // action stack
//     Array_push(as, 1);
//     int look = scan();
//     while(Array_len(as) > 0) {
//         int top = Array_last(as);
//         // nonterminal_p(top)
//         if(top < 6) {
//             int action = act[top][look];
//             if(action == -1) {
//                 printf("syntax error\n");
//                 exit(0);
//             }
//             Array_pop(as);
//             Array_pop(vs);
//             int * symbol = &rhs[prhs[action]];
//             while(* symbol != -1) {
//                 Array_push(as, symbol);
//                 Array_push(vs, symbol);
//                 symbol += 1;
//             }
//         } else if(top > 9) {
//             Array_pop(as);
//             Array_pop(vs);
//             void * val;
//             case(top) {
//             case 9:
//                 val = Array_get(vs, 0, (1) - 1);
//             case 10:
//             default:
//                 break;
//             }
//         } else if(look == top) {
//         } else {
//             printf("syntax error\n");
//         }
//     }
// }

// set id

// set nonterminal id (for row index of table, cell in rhs)

static void
set_NT_id_each_NT(void * _i, void * nonterminal, uint_t index) {
    uint_t * i = _i;
    Nonterminal_set_id(nonterminal, * i);
    * i += 1;
}

// set terminal id (for col index of table, cell in rhs)

static void
set_T_id_each_T(void * _i, void * terminal, uint_t index) {
    uint_t * i = _i;
    Terminal_set_id(terminal, * i);
    * i += 1;
}

// set block id (for cell in rhs)

static void
set_block_id_each_token(void * unused, void * token, uint_t index) {
    char * red = "\e[48;5;52m";
    char * gray = "\e[48;5;235m";
    char * color = index % 2 == 0 ? red : gray;
    printf("%s%s", color, inspect(token));
}

static void
set_block_id_each_block(void * _i, void * block, uint_t index) {
    uint_t * i = _i;
    Block_set_id(block, * i);
    * i += 1;
    Block_expand(block);

    // debug
    void * tokens = Block_tokens(block);
    printf("B[%zu]{", index);
    Array_each(tokens, set_block_id_each_token, NULL);
    char * reset = "\e[0m";
    printf("%s}\n", reset);
}

static void
set_block_id_each_prod(void * i, void * production, uint_t index) {
    Production_each_block(production, set_block_id_each_block, i);
}

static void
set_block_id_each_NT(void * i, void * nonterminal, uint_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, set_block_id_each_prod, i);
}

// set production id (for row of prhs)

static void
set_prod_id_each_prod(void * _production_i, void * production, uint_t index) {
    uint_t * production_i = _production_i;
    Production_set_id(production, * production_i);
    * production_i += 1;
}

static void
set_prod_id_each_NT(void * production_i, void * nonterminal, uint_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, set_prod_id_each_prod, production_i);
}

private
def(set_id, void) {
    uint_t i = 0;
    Array_each(self->nonterminals, set_NT_id_each_NT,  &i);
    Array_each(self->terminals,    set_T_id_each_T,   &i);
    Array_each(self->nonterminals, set_block_id_each_NT, &i);
    uint_t production_i = 0;
    Array_each(self->nonterminals, set_prod_id_each_NT, &production_i);
}

// make table

static void
clear_table(uint_t * table, uint_t rows, uint_t cols) {
    for(uint_t row_i = 0; row_i < rows; row_i += 1) {
        for(uint_t col_i = 0; col_i < cols; col_i += 1) {
            table[row_i * rows + col_i] = -1;
        }
    }
}

struct table {
    uint_t * table;
    uint_t rows;
    void * nonterminal;
    void * production;
};

// fill table by first{terminals}

static void
fill_table_first_each_T(void * _args, void * terminal, void * data) {
    struct table * args = _args;
    uint_t row_i = Nonterminal_id(args->nonterminal);
    uint_t col_i = Terminal_id(terminal) - args->rows;
    uint_t id = Production_id(args->production);
    printf("first  [%s][%s]: %zu\n",
            inspect(Nonterminal_token(args->nonterminal)),
            inspect(terminal),
            id);
    args->table[row_i * args->rows + col_i] = id;
}

static void
fill_table_first_each_prod(void * _args, void * production, uint_t index) {
    struct table * args = _args;
    args->production = production;
    void * first = Production_first(production);
    Hash_each(first, fill_table_first_each_T, args);
}

// fill table by follow{terminals}

static void
fill_table_follow_each_T(void * _args, void * terminal, void * data) {
    struct table * args = _args;
    uint_t row_i = Nonterminal_id(args->nonterminal);
    uint_t col_i = Terminal_id(terminal) - args->rows;
    uint_t id = Production_id(args->production);
    printf("follow [%s][%s]: %zu\n",
            inspect(Nonterminal_token(args->nonterminal)),
            inspect(terminal),
            id);
    args->table[row_i * args->rows + col_i] = id;
}

static void
fill_table_follow_each_prod(void * _args, void * production, uint_t index) {
    if(Production_type(production) == BLANK) {
        struct table * args = _args;
        args->production = production;
        void * follow = Production_follow(production);
        Hash_each(follow, fill_table_follow_each_T, args);
    }
}

// fill table

static void
fill_table_each_NT(void * _args, void * nonterminal, uint_t index) {
    struct table * args = _args;
    args->nonterminal = nonterminal;
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, fill_table_follow_each_prod, args);
    Array_each(productions, fill_table_first_each_prod, args);
}

private
def(fill_table, void : uint_t * @table) {
    struct table args;
    args.table = table;
    args.rows = self->rows;
    Array_each(self->nonterminals, fill_table_each_NT, &args);
}

private
def(make_table, void) {
    uint_t rows = Array_len(self->nonterminals);
    uint_t cols = Array_len(self->terminals);
    uint_t * table = malloc(rows * cols * sizeof(uint_t));
    self->rows = rows;
    self->cols = cols;
    self->table = table;
    clear_table(table, rows, cols);
    fill_table(self, table);
}

// make rhs

struct self_with_token {
    struct Table * self;
    uint_t token_i;
    uint_t block_i;
    uint_t production_i;
    void * production;
    uint_t * rhs;
    uint_t * prhs;
};

// rhs size

static void
rhs_size_each_prod(void * _args, void * production, uint_t index) {
    if(!Production_epsilon(production)) {
        struct self_with_token * args = _args;
        args->token_i += Production_tokens_size(production);
        args->token_i += Production_blocks_size(production);
        args->token_i += 1; // 1 cell == -1
    }
}

static void
rhs_size_each_NT(void * args, void * nonterminal, uint_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, rhs_size_each_prod, args);
}

private
def(rhs_size, uint_t) {
    struct self_with_token args;
    args.self = self;
    args.token_i = 0;
    Array_each(self->nonterminals, rhs_size_each_NT, &args);
    return args.token_i;
}

// prhs size

static void
prhs_size_each_NT(void * _args, void * nonterminal, uint_t index) {
    struct self_with_token * args = _args;
    void * productions = Nonterminal_productions(nonterminal);
    args->token_i += Array_len(productions);
}

private
def(prhs_size, uint_t) {
    struct self_with_token args;
    args.self = self;
    args.token_i = 0;
    Array_each(self->nonterminals, prhs_size_each_NT, &args);
    return args.token_i;
}

// make rhs & prhs

static void
make_rhs_each_token_NT_or_T(void * _args, void * token) {
    struct self_with_token * args = _args;
    uint_t token_id = 0;
    void * nonterminal = NT_of_token(args->self, token);
    void * terminal    =  T_of_token(args->self, token);
    if(nonterminal != NULL) {
        token_id = Nonterminal_id(nonterminal);
    } else if(terminal != NULL) {
        token_id = Terminal_id(terminal);
    }
    args->rhs[args->token_i] = token_id;
    args->token_i += 1;
}

static void
make_rhs_each_token_block(void * _args, uint_t index) {
    struct self_with_token * args = _args;
    uint_t tokens_size = Production_tokens_size(args->production);
    uint_t blocks_size = Production_blocks_size(args->production);
    uint_t block_i = blocks_size - args->block_i - 1;
    void * block = Production_block(args->production, block_i);
    if(block != NULL && index == tokens_size - Block_no(block)) {
        uint_t token_id = Block_id(block);
        printf("token id %zu, block no %zu\n", token_id, Block_no(block));
        args->rhs[args->token_i] = token_id;
        args->token_i += 1;
        args->block_i += 1;
    }
}

static void
make_rhs_each_token(void * args, void * token, uint_t index) {
    make_rhs_each_token_block(args, index);
    make_rhs_each_token_NT_or_T(args, token);
}

static void
make_rhs_each_prod(void * _args, void * production, uint_t index) {
    struct self_with_token * args = _args;
    uint_t token_i = args->token_i;
    if(!Production_epsilon(production)) {
        args->production = production;
        args->block_i = 0;
        Production_reverse_each_token(production, make_rhs_each_token, args);
        uint_t size = Production_tokens_size(production);
        make_rhs_each_token_block(args, size);
        args->rhs[args->token_i] = -1;
        args->token_i += 1;
    } else {
        token_i -= 1;
    }
    args->prhs[args->production_i] = token_i;
    args->production_i += 1;
}

static void
make_rhs_each_NT(void * args, void * nonterminal, uint_t index) {
    void * productions = Nonterminal_productions(nonterminal);
    Array_each(productions, make_rhs_each_prod, args);
}

private
def(make_rhs, void) {
    uint_t   size =  rhs_size(self);
    uint_t p_size = prhs_size(self);
    uint_t *  rhs = malloc(size * sizeof(uint_t));
    uint_t * prhs = malloc(p_size * sizeof(uint_t));
    struct self_with_token args;
    args.self = self;
    args.token_i = 0;
    args.production_i = 0;
    args.rhs = rhs;
    args.prhs = prhs;
    self->rhs = rhs;
    self->prhs = prhs;
    self->rhs_size = size;
    self->prhs_size = p_size;
    Array_each(self->nonterminals, make_rhs_each_NT, &args);
    for(uint_t i = 0; i < size; i++) {
        if(rhs[i] == -1) {
            printf("rhs[  ]\n");
        } else if(rhs[i] < self->rows) {
            printf("rhs[%s]\n", inspect(Nonterminal_token(Array_get(self->nonterminals, rhs[i]))));
        } else if(rhs[i] < self->rows + self->cols) {
            printf("rhs[%s]\n", inspect(Array_get(self->terminals, rhs[i] - self->rows)));
        } else {
            printf("rhs[block %zu]\n", rhs[i] - self->rows - self->cols);
        }
    }
    for(uint_t i = 0; i < p_size; i++) {
        printf("prhs[%zu]\n", prhs[i]);
    }
}

// delete nonterminals, terminals

static void
delete_each_NT(void * unused, void * nonterminal, uint_t index) {
    delete(nonterminal);
}

static void
delete_each_T(void * unused, void * terminal, uint_t index) {
    delete(terminal);
}

static void
delete_NT_and_T_and_sets(struct Table * self) {
    Array_each(self->nonterminals, delete_each_NT, NULL);
    Array_each(self->terminals, delete_each_T, NULL);
    delete(self->nonterminals);
    delete(self->nonterminal_set);
    delete(self->terminals);
    delete(self->terminal_set);
}

private
def(build, void) {
    NT_set_init(self);
    production_epsilon(self);
    T_set_init(self);
    Ts_init(self);
    debug_Ts(self);
    null_init(self);
    first_init(self);
    follow_init(self);
    set_id(self);
    make_table(self);
    make_rhs(self);
    delete_NT_and_T_and_sets(self);
}

// save table

static void
save_col(void * file, uint_t col) {
    if(col == -1) {
        File_puts(file, " -1");
    } else {
        File_printf(file, "%3zu", col);
    }
}

static void
save_row(void * file, uint_t * table,
        uint_t rows, uint_t row_i, uint_t cols, char * line_feed) {
    File_puts(file, "    {");
    for(uint_t col_i = 0; col_i + 1 < cols; col_i++) {
        uint_t col = table[row_i * rows + col_i];
        save_col(file, col);
        File_puts(file, ", ");
    }
    if(cols > 0) {
        uint_t col = table[row_i * rows + cols - 1];
        save_col(file, col);
    }
    File_puts(file, "}");
    File_puts(file, line_feed);
}

static void
save_table(struct Table * self, void * file) {
    uint_t * table = self->table;
    uint_t rows = self->rows;
    uint_t cols = self->cols;
    File_printf(file, "static int act[%zu][%zu] = {\n", rows, cols);
    for(uint_t row_i = 0; row_i + 1 < rows; row_i++) {
        save_row(file, table, rows, row_i, cols, ",\n");
    }
    if(rows > 0) {
        save_row(file, table, rows, rows - 1, cols, "\n");
    }
    File_puts(file, "};\n\n");
}

// save prhs

static void
save_prhs(struct Table * self, void * file) {
    uint_t size = self->prhs_size;
    File_printf(file, "static int prhs[%zu] = {\n", size);
    for(uint_t i = 0; i + 1 < size; i++) {
        File_printf(file, "    %zu,\n", self->prhs[i]);
    }
    if(size > 0) {
        File_printf(file, "    %zu\n", self->prhs[size - 1]);
    }
    File_puts(file, "};\n\n");
}

// save rhs

static void
save_rhs(struct Table * self, void * file) {
    uint_t * rhs = self->rhs;
    uint_t size = self->rhs_size;
    File_printf(file, "static int rhs[%zu] = {\n    ", size);
    for(uint_t i = 0; i + 1 < size; i += 1) {
        if(rhs[i] == -1) {
            File_puts(file, " -1,\n    ");
        } else {
            File_printf(file, "%3zu, ", rhs[i]);
        }
    }
    if(size > 0) {
        File_puts(file, " -1\n");
    }
    File_puts(file, "};\n\n");
}

static void
open_file(void * _self, void * file) {
    struct Table * self = _self;
    save_table(self, file);
    save_prhs(self, file);
    save_rhs(self, file);
    free(self->table);
    free(self->rhs);
    free(self->prhs);
}

private
def(save, void : void * @file) {
    File_open(file, "w", open_file, self);
}

def(write_to, void : void * @file) {
    build(self);
    save(self, file);
}
