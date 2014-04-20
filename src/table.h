#ifndef TABLE_H
#define TABLE_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Table
#define _Table_PUBLIC_OVERRIDE_METHODS \
    (_Table_ctor), \
    (_Table_dtor)
#define _Table_PUBLIC_METHODS \
    (_Table_NT_set_each_NT), \
    (_Table_T_set_each_token), \
    (_Table_T_set_each_prod), \
    (_Table_T_set_each_NT), \
    (_Table_Ts_each_T), \
    (_Table_null_NT), \
    (_Table_null_each_NT), \
    (_Table_debug_Ts), \
    (_Table_build)
#define _Table_PRIVATE_METHODS \
    (_Table_NT_set_init), \
    (_Table_production_epsilon), \
    (_Table_T_set_init), \
    (_Table_Ts_init), \
    (_Table_null_init), \
    (_Table_first_init), \
    (_Table_follow_init), \
    (_Table_set_id), \
    (_Table_fill_table), \
    (_Table_make_table), \
    (_Table_rhs_size), \
    (_Table_prhs_size), \
    (_Table_make_rhs)
#define _Table_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Table_dtor dtor, void
#define _Table_NT_set_each_NT NT_set_each_NT, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_NT_set_init NT_set_init, void
#define _Table_production_epsilon production_epsilon, void
#define _Table_T_set_each_token T_set_each_token, void, (void * token, token), (size_t index, index)
#define _Table_T_set_each_prod T_set_each_prod, void, (void * production, production), (size_t index, index)
#define _Table_T_set_each_NT T_set_each_NT, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_T_set_init T_set_init, void
#define _Table_Ts_each_T Ts_each_T, void, (void * token, token), (void * terminal, terminal)
#define _Table_Ts_init Ts_init, void
#define _Table_null_NT null_NT, void, (void * nonterminal, nonterminal)
#define _Table_null_each_NT null_each_NT, void, (void * nonterminal, nonterminal), (size_t index, index)
#define _Table_null_init null_init, void
#define _Table_debug_Ts debug_Ts, void
#define _Table_first_init first_init, void
#define _Table_follow_init follow_init, void
#define _Table_set_id set_id, void
#define _Table_fill_table fill_table, void, (size_t * table, table)
#define _Table_make_table make_table, void
#define _Table_rhs_size rhs_size, size_t
#define _Table_prhs_size prhs_size, size_t
#define _Table_make_rhs make_rhs, void
#define _Table_build build, void *
def_public_methods()

#endif
