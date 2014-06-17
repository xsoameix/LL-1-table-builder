#ifndef TABLE_H
#define TABLE_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Table
#define _Table_PUBLIC_OVERRIDE_METHODS \
    (_Table_ctor), \
    (_Table_dtor)
#define _Table_PUBLIC_METHODS \
    (_Table_write_to)
#define _Table_PRIVATE_METHODS \
    (_Table_NT_set_init), \
    (_Table_NT_p), \
    (_Table_NT_of_token), \
    (_Table_production_epsilon), \
    (_Table_T_set_init), \
    (_Table_T_p), \
    (_Table_T_of_token), \
    (_Table_Ts_init), \
    (_Table_null_NT), \
    (_Table_null_init), \
    (_Table_first_subset_init), \
    (_Table_traverse_NTs), \
    (_Table_first_init_after_traverse), \
    (_Table_debug_Ts), \
    (_Table_debug_first), \
    (_Table_debug_subset), \
    (_Table_debug_union), \
    (_Table_debug_follow), \
    (_Table_first_init), \
    (_Table_follow_Ts_init), \
    (_Table_follow_subset_init), \
    (_Table_follow_init_after_traverse), \
    (_Table_follow_clear_set), \
    (_Table_follow_init), \
    (_Table_set_id), \
    (_Table_fill_table), \
    (_Table_make_table), \
    (_Table_rhs_size), \
    (_Table_prhs_size), \
    (_Table_make_rhs), \
    (_Table_build), \
    (_Table_save)
#define _Table_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Table_dtor dtor, void
#define _Table_NT_set_init NT_set_init, void
#define _Table_NT_p NT_p, bool, (void * token, token)
#define _Table_NT_of_token NT_of_token, void *, (void * token, token)
#define _Table_production_epsilon production_epsilon, void
#define _Table_T_set_init T_set_init, void
#define _Table_T_p T_p, bool, (void * token, token)
#define _Table_T_of_token T_of_token, void *, (void * token, token)
#define _Table_Ts_init Ts_init, void
#define _Table_null_NT null_NT, void, (void * nonterminal, nonterminal)
#define _Table_null_init null_init, void
#define _Table_first_subset_init first_subset_init, void
#define _Table_traverse_NTs traverse_NTs, void
#define _Table_first_init_after_traverse first_init_after_traverse, void
#define _Table_debug_Ts debug_Ts, void
#define _Table_debug_first debug_first, void
#define _Table_debug_subset debug_subset, void
#define _Table_debug_union debug_union, void
#define _Table_debug_follow debug_follow, void
#define _Table_first_init first_init, void
#define _Table_follow_Ts_init follow_Ts_init, void
#define _Table_follow_subset_init follow_subset_init, void
#define _Table_follow_init_after_traverse follow_init_after_traverse, void
#define _Table_follow_clear_set follow_clear_set, void
#define _Table_follow_init follow_init, void
#define _Table_set_id set_id, void
#define _Table_fill_table fill_table, void, (size_t * table, table)
#define _Table_make_table make_table, void
#define _Table_rhs_size rhs_size, size_t
#define _Table_prhs_size prhs_size, size_t
#define _Table_make_rhs make_rhs, void
#define _Table_build build, void
#define _Table_save save, void, (void * file, file)
#define _Table_write_to write_to, void, (void * file, file)
def_public_methods()

#endif
