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
    (_Table_first_init_NT), \
    (_Table_first_init_NTs), \
    (_Table_first_init_traverse), \
    (_Table_first_init), \
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
#define _Table_first_init_NT first_init_NT, void, (void * nonterminal, nonterminal)
#define _Table_first_init_NTs first_init_NTs, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init_traverse first_init_traverse, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_first_init first_init, void
#define _Table_build build, void *
def_public_methods()

#endif
