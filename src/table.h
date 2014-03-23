#ifndef TABLE_H
#define TABLE_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Table
#define _Table_PUBLIC_OVERRIDE_METHODS \
    (_Table_ctor), \
    (_Table_dtor)
#define _Table_PUBLIC_METHODS \
    (_Table_NT_set_init_iter), \
    (_Table_NT_set_init), \
    (_Table_T_set_init_token_iter), \
    (_Table_T_set_init_stmt_iter), \
    (_Table_T_set_init_iter), \
    (_Table_T_set_init), \
    (_Table_Ts_init_iter), \
    (_Table_Ts_init), \
    (_Table_null_init_NT), \
    (_Table_null_init_iter), \
    (_Table_null_init), \
    (_Table_first_init_subset), \
    (_Table_first_init_traverse), \
    (_Table_first_init_union_set), \
    (_Table_first_init_debug_first), \
    (_Table_follow_init_debug_follow), \
    (_Table_first_init_debug_subset), \
    (_Table_first_init_debug_union_set), \
    (_Table_first_init), \
    (_Table_follow_init_follow), \
    (_Table_follow_init_subset), \
    (_Table_follow_init), \
    (_Table_build)
#define _Table_PRIVATE_METHODS
#define _Table_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Table_dtor dtor, void
#define _Table_NT_set_init_iter NT_set_init_iter, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_NT_set_init NT_set_init, void
#define _Table_T_set_init_token_iter T_set_init_token_iter, void, (void * token, token), (size_t index, index)
#define _Table_T_set_init_stmt_iter T_set_init_stmt_iter, void, (void * stmt, stmt), (size_t index, index)
#define _Table_T_set_init_iter T_set_init_iter, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_T_set_init T_set_init, void
#define _Table_Ts_init_iter Ts_init_iter, void, (void * terminal, terminal), (void * data, data)
#define _Table_Ts_init Ts_init, void
#define _Table_null_init_NT null_init_NT, void, (void * nonterminal, nonterminal)
#define _Table_null_init_iter null_init_iter, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_null_init null_init, void
#define _Table_first_init_subset first_init_subset, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_traverse first_init_traverse, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_union_set first_init_union_set, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_debug_first first_init_debug_first, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_follow_init_debug_follow follow_init_debug_follow, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_debug_subset first_init_debug_subset, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_debug_union_set first_init_debug_union_set, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init first_init, void
#define _Table_follow_init_follow follow_init_follow, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_follow_init_subset follow_init_subset, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_follow_init follow_init, void
#define _Table_build build, void *
def_public_methods()

#endif
