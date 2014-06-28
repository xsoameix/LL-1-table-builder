#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libooc/hash.h>
#include <libooc/array.h>
#include <libooc/file.h>
#include <libooc/inttype.h>
#include <libooc/object_type.h>
#include <libooc/array_macro.h>
#include <libooc/hash_macro.h>

#include "token.h"
#include "terminal.h"
#include "nonterminal.h"
#include "production.h"
#include "block.h"
#include "table.struct.h"

#define SELF ((struct O_CLASS *) self)
#define NT_SET SELF->nonterminal_set
#define NTS SELF->nonterminals
#define T_SET SELF->terminal_set
#define TS SELF->terminals
#define TABLE SELF->table
#define ROWS SELF->rows
#define COLS SELF->cols
#define RHS SELF->rhs
#define RHS_LEN SELF->rhs_len
#define PRHS SELF->prhs
#define PRHS_LEN SELF->prhs_len
#define NT ITEM
#define T ITEM
#define TOK ITEM
#define PROD ITEM
#define BLOCK ITEM
#define NT_P(token) NT_p(SELF, token)
#define NT_OF(token) NT_of_token(self, token)
#define T_OF(token) T_of_token(self, token)
#define SET_NULL(nt) NT_set_null(self, nt)
#define TYPE_OF_NT(nt) Nonterminal_type(nt)
#define SET_NT_TYPE(...) Nonterminal_set_type(__VA_ARGS__)
#define TOK_OF(...) Nonterminal_token(__VA_ARGS__)
#define PRODS_OF(...) Nonterminal_productions(__VA_ARGS__)
#define SET_ID_OF_NT(...) Nonterminal_set_id(__VA_ARGS__)
#define ID_OF_NT(...) Nonterminal_id(__VA_ARGS__)
#define SET_ID_OF_T(...) Terminal_set_id(__VA_ARGS__)
#define ID_OF_T(...) Terminal_id(__VA_ARGS__)
#define TOKS_OF(...) Production_tokens(__VA_ARGS__)
#define SET_EPSILON(...) Production_set_epsilon(__VA_ARGS__)
#define SET_PROD_TYPE(...) Production_set_type(__VA_ARGS__)
#define SET_DONE(...) Production_set_done(__VA_ARGS__)
#define SET_ID_OF_PROD(...) Production_set_id(__VA_ARGS__)
#define ID_OF_PROD(...) Production_id(__VA_ARGS__)
#define EPSILON_OF(...) Production_epsilon(__VA_ARGS__)
#define INIT_FIRST_OF(...) Production_first_init(__VA_ARGS__)
#define INIT_FOLLOW_OF(...) Production_follow_init(__VA_ARGS__)
#define FIRST_OF(...) Production_first(__VA_ARGS__)
#define FOLLOW_OF(...) Production_follow(__VA_ARGS__)
#define SUBSET_OF(...) Production_subset(__VA_ARGS__)
#define UNION_OF(...) Production_union_set(__VA_ARGS__)
#define TRAVERSED_OF(...) Production_traversed(__VA_ARGS__)
#define TRAVERSED_BY(...) Production_traversed_by_p(__VA_ARGS__)
#define DONE_P(...) Production_done_p(__VA_ARGS__)
#define TYPE_OF_PROD(...) Production_type(__VA_ARGS__)
#define NO_OF(...) Production_no(__VA_ARGS__)
#define CLEAR_SET(...) Production_clear_set(__VA_ARGS__)
#define TOKS_LEN(...) Production_tokens_len(__VA_ARGS__)
#define BLOCKS_LEN(...) Production_blocks_len(__VA_ARGS__)
#define BLOCKS_P(...) Production_blocks_p(__VA_ARGS__)
#define BLOCK_OF(...) Production_block(__VA_ARGS__)
#define BLOCKS_OF(...) Production_blocks(__VA_ARGS__)

typedef enum NT_TYPE TYPE;

O_DEF_CLASS(Table, Object)

override
def(ctor, void : va_list * @args_ptr) {
    NTS = va_arg(* args_ptr, o);
}

override
def(dtor, void) {
    free(self);
}

// NT set

private
def(NT_set_init, void) {

    NT_SET = new(Hash);

    ITOR(nt) {
        Hash_set(NT_SET, TOK_OF(NT), NT);
    }

    EACH(NTS, nt);
}

private
def(NT_p, bool : o @tok) {
    return H_GET(NT_SET, tok) != NULL;
}

private
def(NT_of_token, o : o @tok) {
    o nt = H_GET(NT_SET, tok);
    return nt == NULL ? 0 : nt;
}

// production epsilon

private
def(prod_epsilon, void) {

    ITOR(prod) {
        o ts = TOKS_OF(PROD);
        if(LEN(ts) != 1) return;
        o t = GET(ts, 0);
        if(!NT_P(t) && strcmp(inspect(t), "epsilon") == 0) {
            SET_EPSILON(PROD, true);
        }
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// T set

private
def(T_set_init, void) {

    ITOR(tok) {
        if(!NT_P(TOK)) {
            o t = new(Terminal, TOK);
            H_SET(T_SET, TOK, t);
        }
    }

    ITOR(prod) {
        if(!EPSILON_OF(PROD)) {
            EACH(TOKS_OF(PROD), tok);
        }
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    T_SET = new(Hash);
    EACH(NTS, nt);
}

private
def(T_p, bool : o @tok) {
    return H_GET(T_SET, tok) != NULL;
}

private
def(T_of_token, o : o @tok) {
    o t = H_GET(T_SET, tok);
    return t == NULL ? 0 : t;
}

// Ts

private
def(Ts_init, void) {
    TS = H_VALUES(T_SET);
}

// null ?

private
def(set_NT_type, void : o @nt) {

    ANY_P_ITOR(tok_present_p) {
        o nt_, t;
        if((nt_ = NT_OF(TOK)) && nt_ != nt) {
            printf("NT[%s]\n", inspect(TOK));
            set_NT_type(self, nt_);
            if(TYPE_OF_NT(nt_) == PRESENT) return true;
        } else if(t = T_OF(TOK)) {
            printf("T[%s]\n", inspect(TOK));
            return true;
        } else {
            printf("%s\n", inspect(TOK));
        }
        return false;
    }

    ANY_P_ITOR(prod_blank_p) {
        bool present = ANY_P(TOKS_OF(PROD), tok_present_p);
        SET_PROD_TYPE(PROD, present ? PRESENT : BLANK);
        return !present;
    }

    if(TYPE_OF_NT(nt) == NOT_SET) {
        TYPE type = ANY_P(PRODS_OF(nt), prod_blank_p) ? BLANK : PRESENT;
        SET_NT_TYPE(nt, type);
        printf("--- %s %s ---\n",
                inspect(TOK_OF(nt)),
                type == PRESENT ? "T" : "F");
    }
}

private
def(null_init, void) {

    ITOR(nt) {
        set_NT_type(self, NT);
    }

    EACH(NTS, nt);
}

// traverse algorithm
// anc: ancestor

static void
traverse(o prod, o anc) {

    // traverse_add NT, prod

    void add_prod_to_anc(o prod) {
        H_SET(UNION_OF(anc), prod, prod);
    }

    H_ITOR(add_prod_to_anc) {
        add_prod_to_anc(KEY);
    }

    void add_anc_to_prod(o prod) {
        H_SET(TRAVERSED_OF(prod), anc, anc);
    }

    // traverse NT, prod

    ITOR(prod) {
        traverse(PROD, anc);
    }

    H_ITOR(nt) {
        EACH(PRODS_OF(KEY), prod);
    }

    printf("ancestor[%s][%zu] P[%s][%zu]\n",
            inspect(anc),
            NO_OF(anc),
            inspect(prod),
            NO_OF(prod));
    if(!TRAVERSED_BY(prod, anc)) {
        if(DONE_P(prod)) {
            H_EACH(UNION_OF(prod), add_prod_to_anc);
        } else {
            add_prod_to_anc(prod);
            add_anc_to_prod(prod);
            H_EACH(SUBSET_OF(prod), nt);
        }
    }
    printf("ancestor[%s][%zu] ---\n",
            inspect(anc),
            NO_OF(anc));
}

// first

// set first{terminals} & subset{nonterminals}

private
def(first_subset_init, void) {

    ANY_P_ITOR(tok, o prod) {
        o nt, t;
        if(nt = NT_OF(TOK)) {
            H_SET(SUBSET_OF(prod), nt, nt);
            return TYPE_OF_NT(nt) == PRESENT;
        } else if(t = T_OF(TOK)) {
            H_SET(FIRST_OF(prod), t, t);
            return true;
        } else {
            return false;
        }
    }

    ITOR(prod) {
        INIT_FIRST_OF(PROD);
        ANY_P(TOKS_OF(PROD), tok, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// set union_set{productions}

private
def(traverse_NTs, void) {

    ITOR(prod) {
        traverse(PROD, PROD);
        SET_DONE(PROD, true);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
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

    H_ITOR(t, o prod) {
        H_SET(FIRST_OF(prod), KEY, KEY);
    }

    H_ITOR(prod, o prod) {
        H_EACH(FIRST_OF(KEY), t, prod);
    }

    ITOR(prod) {
        H_EACH(UNION_OF(PROD), prod, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// debug: terminals

private
def(debug_Ts, void) {

    ITOR(t) {
        printf("T: %s\n", inspect(T));
    }

    EACH(TS, t);
}

// debug: first{terminals}

private
def(debug_first, void) {

    H_ITOR(t, o prod) {
        printf("first[%s][%zu][%s]: %s\n",
                inspect(prod),
                NO_OF(prod),
                TYPE_OF_PROD(prod) == PRESENT ? "T" : (
                    TYPE_OF_PROD(prod) == BLANK ? "F" : "?"),
                inspect(KEY));
    }

    ITOR(prod) {
        H_EACH(FIRST_OF(PROD), t, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// debug: subset{nonterminals}

private
def(debug_subset, void) {

    H_ITOR(nt_of_subset, o prod) {
        printf("subset[%s][%zu](%p): %s\n",
                inspect(prod),
                NO_OF(prod),
                prod,
                inspect(TOK_OF(KEY)));
    }

    ITOR(prod) {
        H_EACH(SUBSET_OF(PROD), nt_of_subset, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// debug: union{productions}

private
def(debug_union, void) {

    H_ITOR(tok, o prod) {
        printf("union[%s][%zu]: [%s][%zu]\n",
                inspect(prod),
                NO_OF(prod),
                inspect(KEY),
                NO_OF(KEY));
    }

    ITOR(prod) {
        H_EACH(UNION_OF(PROD), tok, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// debug: follow{terminals}

private
def(debug_follow, void) {

    H_ITOR(t, o prod) {
        printf("follow[%s][%zu][%s]: %s\n",
                inspect(prod),
                NO_OF(prod),
                TYPE_OF_PROD(prod) == PRESENT ? " " : (
                    TYPE_OF_PROD(prod) == BLANK ? "F" : "?"),
                inspect(KEY));
    }

    ITOR(prod) {
        H_EACH(FOLLOW_OF(PROD), t, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
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

    ITOR(prod) {
        INIT_FOLLOW_OF(PROD);
        SET_DONE(PROD, false);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

private
def(follow_subset_init, void) {

    // merge next nonterminal into subset{nonterminals}

    ITOR(add_next_NT_to_subset, o nt) {
        H_SET(SUBSET_OF(PROD), nt, nt);
        printf("  (%s)[%zu] << NT[%s]\n",
                inspect(PROD),
                NO_OF(PROD),
                inspect(TOK_OF(nt)));
    }

    // merge first{terminals} of next nonterminal into follow{terminals}

    ITOR(add_first_of_next_NT_to_follow, o nt) {

        ITOR(prod, o t) {
            H_SET(FOLLOW_OF(PROD), t, t);
            printf("  (%s)[%zu] << T:first[%s]\n",
                    inspect(PROD),
                    NO_OF(PROD),
                    inspect(t));
        }

        H_ITOR(nt, o nt) {
            EACH(PRODS_OF(nt), prod, KEY);
        }

        H_EACH(FIRST_OF(PROD), nt, nt);
    }

    // merge next terminal into follow{terminals}

    ITOR(add_next_T_to_follow, o t) {
        H_SET(FOLLOW_OF(PROD), t, t);
        printf("  (%s)[%zu] << T[%s]\n",
                inspect(PROD),
                NO_OF(PROD),
                inspect(t));
    }

    // merge the nonterminal on the left hand side into subset{nonterminals}

    ITOR(add_LHS_NT_to_subset, o nt) {
        H_SET(SUBSET_OF(PROD), nt, nt);
        printf("  (%s)[%zu] << NT:LHS[%s]\n",
                inspect(PROD),
                NO_OF(PROD),
                inspect(TOK_OF(nt)));
    }

    // set follow{terminals} & subset{nonterminals}

    ITOR(tok, o nt, o prod) {
        o nt_of_tok = NT_OF(TOK);
        if(!nt_of_tok) return;
        printf("  (%s)\n", inspect(TOK_OF(nt_of_tok)));
        o toks = TOKS_OF(prod);
        uint_t len = LEN(toks);
        INDEX += 1;
        while(INDEX < len) {
            o next_tok = GET(toks, INDEX);
            o next_nt, next_t;
            if(next_nt = NT_OF(next_tok)) {
                // merge first{terminals} of next nonterminal into follow{terminals}
                EACH(PRODS_OF(next_nt), add_first_of_next_NT_to_follow, nt_of_tok);

                if(TYPE_OF_NT(next_nt) == PRESENT) return;

                // merge next nonterminal into subset{nonterminals}
                EACH(PRODS_OF(nt_of_tok), add_next_NT_to_subset, next_nt);
            } else if(next_t = T_OF(next_tok)) {
                // merge next terminal into follow{terminals}
                EACH(PRODS_OF(nt_of_tok), add_next_T_to_follow, next_t);
                return;
            }
            INDEX += 1;
        }
        // merge the nonterminal on the left hand side into subset{nonterminals}
        EACH(PRODS_OF(nt_of_tok), add_LHS_NT_to_subset, nt);
    }

    ITOR(prod, o nt) {
        EACH(TOKS_OF(PROD), tok, nt, PROD);
    }

    ITOR(nt) {
        printf("[%s]\n", inspect(TOK_OF(NT)));
        EACH(PRODS_OF(NT), prod, NT);
    }

    EACH(NTS, nt);
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

    H_ITOR(t, o prod) {
        H_SET(FOLLOW_OF(prod), KEY, KEY);
    }

    H_ITOR(prod, o prod) {
        H_EACH(FOLLOW_OF(KEY), t, prod);
    }

    ITOR(prod) {
        H_EACH(UNION_OF(PROD), prod, PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
}

// follow clear set: subset, union_set, traversed

private
def(follow_clear_set, void) {

    ITOR(prod) {
        CLEAR_SET(PROD);
    }

    ITOR(nt) {
        EACH(PRODS_OF(NT), prod);
    }

    EACH(NTS, nt);
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

private
def(set_id, void) {

    // set nonterminal id (for row index of table, cell in rhs)

    ITOR(set_NT_id, o _i) {
        uint_t * i = _i;
        SET_ID_OF_NT(NT, * i);
        * i += 1;
    }

    // set terminal id (for col index of table, cell in rhs)

    ITOR(set_T_id, o _i) {
        uint_t * i = _i;
        SET_ID_OF_T(T, * i);
        * i += 1;
    }

    // set block id (for cell in rhs)

    ITOR(set_block_id, o i) {

        ITOR(tok) {
            char * red = "\e[48;5;52m";
            char * gray = "\e[48;5;235m";
            char * color = INDEX % 2 == 0 ? red : gray;
            printf("%s%s", color, inspect(TOK));
        }

        ITOR(block, o _i) {
            uint_t * i = _i;
            Block_set_id(BLOCK, * i);
            * i += 1;
            Block_expand(BLOCK);

            // debug
            printf("B[%zu]{", INDEX);
            EACH(Block_tokens(BLOCK), tok);
            char * reset = "\e[0m";
            printf("%s}\n", reset);
        }

        ITOR(prod, o i) {
            if(BLOCKS_P(PROD)) EACH(BLOCKS_OF(PROD), block, i);
        }

        EACH(PRODS_OF(NT), prod, i);
    }

    // set production id (for row of prhs)

    ITOR(set_prod_id, o i) {

        ITOR(prod, o _i) {
            uint_t * i = _i;
            SET_ID_OF_PROD(PROD, * i);
            * i += 1;
        }

        EACH(PRODS_OF(NT), prod, i);
    }

    uint_t i = 0;
    EACH(NTS, set_NT_id,    (o) &i);
    EACH(TS,  set_T_id,     (o) &i);
    EACH(NTS, set_block_id, (o) &i);
    i = 0;
    EACH(NTS, set_prod_id,  (o) &i);
}

// make table

private
def(clear_table, void) {
    for(uint_t row_i = 0; row_i < ROWS; row_i += 1) {
        for(uint_t col_i = 0; col_i < COLS; col_i += 1) {
            TABLE[row_i * COLS + col_i] = -1;
        }
    }
}

// fill table

private
def(fill_table, void) {

    // fill table by first{terminals}

    ITOR(first, o nt) {

        H_ITOR(t, o nt, o prod) {
            uint_t row_i = ID_OF_NT(nt);
            uint_t col_i = ID_OF_T(KEY) - ROWS;
            uint_t id = ID_OF_PROD(prod);
            printf("first  [%s][%s]: %zu\n",
                    inspect(TOK_OF(nt)),
                    inspect(KEY),
                    id);
            TABLE[row_i * COLS + col_i] = id;
        }

        H_EACH(FIRST_OF(PROD), t, nt, PROD);
    }

    // fill table by follow{terminals}

    ITOR(follow, o nt) {

        H_ITOR(t, o nt, o prod) {
            uint_t row_i = ID_OF_NT(nt);
            uint_t col_i = ID_OF_T(KEY) - ROWS;
            uint_t id = ID_OF_PROD(prod);
            printf("follow [%s][%s]: %zu\n",
                    inspect(TOK_OF(nt)),
                    inspect(KEY),
                    id);
            uint_t col = row_i * COLS + col_i;
            if(TABLE[col] == -1) {
                TABLE[col] = id;
            } else if(TABLE[col] != id) {
                printf("Follow conflict P[%zu], P[%zu]\n", TABLE[col], id);
                exit(EXIT_FAILURE);
            }
        }

        if(TYPE_OF_PROD(PROD) == BLANK) {
            H_EACH(FOLLOW_OF(PROD), t, nt, PROD);
        }
    }

    ITOR(nt) {
        o prods = PRODS_OF(NT);
        EACH(prods, first, NT);
        EACH(prods, follow, NT);
    }

    EACH(NTS, nt);
}

private
def(make_table, void) {
    ROWS = LEN(NTS);
    COLS = LEN(TS);
    TABLE = malloc(ROWS * COLS * sizeof(uint_t));
    clear_table(self);
    fill_table(self);
}

// make rhs

// rhs size

private
def(rhs_size, uint_t) {

    ITOR(prod, o _i) {
        if(!EPSILON_OF(PROD)) {
            uint_t * i = _i;
            * i += (TOKS_LEN(PROD) +
                    BLOCKS_LEN(PROD) +
                    1); // 1 cell == -1
        }
    }

    ITOR(nt, o i) {
        EACH(PRODS_OF(NT), prod, i);
    }

    uint_t i = 0;
    EACH(NTS, nt, (o) &i);
    return i;
}

// prhs size

private
def(prhs_size, uint_t) {

    ITOR(nt, o _i) {
        uint_t * i = _i;
        * i += LEN(PRODS_OF(NT));
    }

    uint_t i = 0;
    EACH(NTS, nt, (o) &i);
    return i;
}

// make rhs & prhs

private
def(make_rhs, void) {

    void NT_or_T(o tok, uint_t * i) {
        o nt, t;
        if(nt = NT_OF(tok)) {
            RHS[* i] = ID_OF_NT(nt);
        } else if(t = T_OF(tok)) {
            RHS[* i] = ID_OF_T(t);
        }
        * i += 1;
    }

    void block(uint_t reverse_i, o prod, uint_t * i, uint_t * block_i) {
        o block = BLOCK_OF(prod, - (* block_i) - 1);
        if(block && reverse_i + Block_no(block) == TOKS_LEN(prod)) {
            printf("token id %zu, block no %zu\n", Block_id(block), Block_no(block));
            RHS[* i] = Block_id(block);
            * i += 1;
            * block_i += 1;
        }
    }

    ITOR(tok, o prod, o _tok_i, o _block_i) {
        uint_t * tok_i = _tok_i;
        uint_t * block_i = _block_i;

        // block is the following of NT_or_T.
        block(INDEX, prod, tok_i, block_i);
        NT_or_T(TOK, tok_i);
    }

    ITOR(prod, o _prod_i, o _tok_i) {
        uint_t * prod_i = _prod_i;
        uint_t * tok_i = _tok_i;
        PRHS[* prod_i] = * tok_i;
        if(!EPSILON_OF(PROD)) {
            uint_t block_i = 0;
            REVERSE_EACH(TOKS_OF(PROD), tok, PROD, tok_i, &block_i);
            block(TOKS_LEN(PROD), PROD, tok_i, &block_i);
            RHS[* tok_i] = -1;
            * tok_i += 1;
        } else {
            PRHS[* prod_i] -= 1;
        }
        * prod_i += 1;
    }

    ITOR(nt, o prod_i, o tok_i) {
        EACH(PRODS_OF(NT), prod, prod_i, tok_i);
    }

    RHS_LEN  = rhs_size(self);
    PRHS_LEN = prhs_size(self);
    RHS = malloc(RHS_LEN * sizeof(uint_t));
    PRHS = malloc(PRHS_LEN * sizeof(uint_t));
    uint_t prod_i = 0;
    uint_t tok_i = 0;
    EACH(NTS, nt, &prod_i, &tok_i);
    for(uint_t i = 0; i < RHS_LEN; i++) {
        if(RHS[i] == -1) {
            printf("rhs[  ]\n");
        } else if(RHS[i] < ROWS) {
            printf("rhs[%s]\n", inspect(TOK_OF(GET(NTS, RHS[i]))));
        } else if(RHS[i] < ROWS + COLS) {
            printf("rhs[%s]\n", inspect(GET(TS, RHS[i] - ROWS)));
        } else {
            printf("rhs[block %zu]\n", RHS[i] - ROWS - COLS);
        }
    }
    for(uint_t i = 0; i < PRHS_LEN; i++) {
        printf("prhs[%zu]\n", PRHS[i]);
    }
}

// delete nonterminals, terminals

private
def(delete_NT_and_T_and_sets, void) {

    ITOR(nt) {
        delete(NT);
    }

    ITOR(t) {
        delete(T);
    }

    EACH(NTS, nt);
    EACH(TS, t);
    delete(NTS);
    delete(NT_SET);
    delete(TS);
    delete(T_SET);
}

private
def(build, void) {
    NT_set_init(self);
    prod_epsilon(self);
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

private
def(save_table, void : o @file) {

    void save_col(o file, uint_t col) {
        if(col == -1) {
            File_puts(file, " -1");
        } else {
            File_printf(file, "%3zu", col);
        }
    }

    void save_row(o file, uint_t row_i, char * line_feed) {
        File_puts(file, "    {");
        for(uint_t col_i = 0; col_i + 1 < COLS; col_i++) {
            save_col(file, TABLE[row_i * COLS + col_i]);
            File_puts(file, ", ");
        }
        if(COLS > 0) {
            save_col(file, TABLE[row_i * COLS + COLS - 1]);
        }
        File_puts(file, "}");
        File_puts(file, line_feed);
    }

    File_printf(file, "static int act[%zu][%zu] = {\n", ROWS, COLS);
    for(uint_t row_i = 0; row_i + 1 < ROWS; row_i++) {
        save_row(file, row_i, ",\n");
    }
    if(ROWS > 0) {
        save_row(file, ROWS - 1, "\n");
    }
    File_puts(file, "};\n\n");
}

// save prhs

private
def(save_prhs, void : o @file) {
    File_printf(file, "static int prhs[%zu] = {\n", PRHS_LEN);
    for(uint_t i = 0; i + 1 < PRHS_LEN; i++) {
        File_printf(file, "    %zu,\n", PRHS[i]);
    }
    if(PRHS_LEN > 0) {
        File_printf(file, "    %zu\n",  PRHS[PRHS_LEN - 1]);
    }
    File_puts(file, "};\n\n");
}

// save rhs

private
def(save_rhs, void : o @file) {
    File_printf(file, "static int rhs[%zu] = {\n    ", RHS_LEN);
    for(uint_t i = 0; i + 1 < RHS_LEN; i += 1) {
        if(RHS[i] == -1) {
            File_printf(file, " -1,\n    ");
        } else {
            File_printf(file, "%3zu, ", RHS[i]);
        }
    }
    if(RHS_LEN > 0) {
        File_puts(file, " -1\n");
    }
    File_puts(file, "};\n\n");
}

private
def(save, void : o @file) {

    void open_file(o file) {
        save_table(self, file);
        save_prhs(self, file);
        save_rhs(self, file);
        free(TABLE);
        free(RHS);
        free(PRHS);
    }

    File_open(file, "w", open_file);
}

def(write_to, void : o @file) {
    build(self);
    save(self, file);
}
