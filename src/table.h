#ifndef O_TABLE_H
#define O_TABLE_H

#include <libooc/object.h>


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Table
#define O_PARENT Object
#define O_Table_OVERRIDE_METHODS_LEN 2
#define O_Table_PUBLIC_METHODS_LEN 1
#define O_Table_PRIVATE_METHODS_LEN 32
#define O_Table_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Table_OVERRIDE_METHOD_1 dtor, void
#define O_Table_PUBLIC_METHOD_0 write_to, void, (void * file, file)
#define O_Table_PRIVATE_METHOD_0 NT_set_init, void
#define O_Table_PRIVATE_METHOD_1 NT_p, bool, (void * token, token)
#define O_Table_PRIVATE_METHOD_2 NT_of_token, void *, (void * token, token)
#define O_Table_PRIVATE_METHOD_3 production_epsilon, void
#define O_Table_PRIVATE_METHOD_4 T_set_init, void
#define O_Table_PRIVATE_METHOD_5 T_p, bool, (void * token, token)
#define O_Table_PRIVATE_METHOD_6 T_of_token, void *, (void * token, token)
#define O_Table_PRIVATE_METHOD_7 Ts_init, void
#define O_Table_PRIVATE_METHOD_8 null_NT, void, (void * nonterminal, nonterminal)
#define O_Table_PRIVATE_METHOD_9 null_init, void
#define O_Table_PRIVATE_METHOD_10 first_subset_init, void
#define O_Table_PRIVATE_METHOD_11 traverse_NTs, void
#define O_Table_PRIVATE_METHOD_12 first_init_after_traverse, void
#define O_Table_PRIVATE_METHOD_13 debug_Ts, void
#define O_Table_PRIVATE_METHOD_14 debug_first, void
#define O_Table_PRIVATE_METHOD_15 debug_subset, void
#define O_Table_PRIVATE_METHOD_16 debug_union, void
#define O_Table_PRIVATE_METHOD_17 debug_follow, void
#define O_Table_PRIVATE_METHOD_18 first_init, void
#define O_Table_PRIVATE_METHOD_19 follow_Ts_init, void
#define O_Table_PRIVATE_METHOD_20 follow_subset_init, void
#define O_Table_PRIVATE_METHOD_21 follow_init_after_traverse, void
#define O_Table_PRIVATE_METHOD_22 follow_clear_set, void
#define O_Table_PRIVATE_METHOD_23 follow_init, void
#define O_Table_PRIVATE_METHOD_24 set_id, void
#define O_Table_PRIVATE_METHOD_25 fill_table, void, (ooc_uint * table, table)
#define O_Table_PRIVATE_METHOD_26 make_table, void
#define O_Table_PRIVATE_METHOD_27 rhs_size, ooc_uint
#define O_Table_PRIVATE_METHOD_28 prhs_size, ooc_uint
#define O_Table_PRIVATE_METHOD_29 make_rhs, void
#define O_Table_PRIVATE_METHOD_30 build, void
#define O_Table_PRIVATE_METHOD_31 save, void, (void * file, file)
#define O_Table_ctor O_Table_OVERRIDE_METHOD_0
#define O_Table_dtor O_Table_OVERRIDE_METHOD_1
#define O_Table_write_to O_Table_PUBLIC_METHOD_0
#define O_Table_NT_set_init O_Table_PRIVATE_METHOD_0
#define O_Table_NT_p O_Table_PRIVATE_METHOD_1
#define O_Table_NT_of_token O_Table_PRIVATE_METHOD_2
#define O_Table_production_epsilon O_Table_PRIVATE_METHOD_3
#define O_Table_T_set_init O_Table_PRIVATE_METHOD_4
#define O_Table_T_p O_Table_PRIVATE_METHOD_5
#define O_Table_T_of_token O_Table_PRIVATE_METHOD_6
#define O_Table_Ts_init O_Table_PRIVATE_METHOD_7
#define O_Table_null_NT O_Table_PRIVATE_METHOD_8
#define O_Table_null_init O_Table_PRIVATE_METHOD_9
#define O_Table_first_subset_init O_Table_PRIVATE_METHOD_10
#define O_Table_traverse_NTs O_Table_PRIVATE_METHOD_11
#define O_Table_first_init_after_traverse O_Table_PRIVATE_METHOD_12
#define O_Table_debug_Ts O_Table_PRIVATE_METHOD_13
#define O_Table_debug_first O_Table_PRIVATE_METHOD_14
#define O_Table_debug_subset O_Table_PRIVATE_METHOD_15
#define O_Table_debug_union O_Table_PRIVATE_METHOD_16
#define O_Table_debug_follow O_Table_PRIVATE_METHOD_17
#define O_Table_first_init O_Table_PRIVATE_METHOD_18
#define O_Table_follow_Ts_init O_Table_PRIVATE_METHOD_19
#define O_Table_follow_subset_init O_Table_PRIVATE_METHOD_20
#define O_Table_follow_init_after_traverse O_Table_PRIVATE_METHOD_21
#define O_Table_follow_clear_set O_Table_PRIVATE_METHOD_22
#define O_Table_follow_init O_Table_PRIVATE_METHOD_23
#define O_Table_set_id O_Table_PRIVATE_METHOD_24
#define O_Table_fill_table O_Table_PRIVATE_METHOD_25
#define O_Table_make_table O_Table_PRIVATE_METHOD_26
#define O_Table_rhs_size O_Table_PRIVATE_METHOD_27
#define O_Table_prhs_size O_Table_PRIVATE_METHOD_28
#define O_Table_make_rhs O_Table_PRIVATE_METHOD_29
#define O_Table_build O_Table_PRIVATE_METHOD_30
#define O_Table_save O_Table_PRIVATE_METHOD_31
O_DEF_GLOBAL_METHODS()

#endif
