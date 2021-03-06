#ifndef O_PRODUCTION_H
#define O_PRODUCTION_H

#include <libooc/object.h>
#include "nonterminal_type.h"


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Production
#define O_PARENT Object
#define O_Production_OVERRIDE_METHODS_LEN 3
#define O_Production_PUBLIC_METHODS_LEN 26
#define O_Production_PRIVATE_METHODS_LEN 0
#define O_Production_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Production_OVERRIDE_METHOD_1 dtor, void
#define O_Production_OVERRIDE_METHOD_2 inspect, char *
#define O_Production_PUBLIC_METHOD_0 no, o_uint
#define O_Production_PUBLIC_METHOD_1 tokens, void *
#define O_Production_PUBLIC_METHOD_2 tokens_len, o_uint
#define O_Production_PUBLIC_METHOD_3 add_token, void, (void * token, token)
#define O_Production_PUBLIC_METHOD_4 block, void *, (o_uint index, index)
#define O_Production_PUBLIC_METHOD_5 create_block, void *
#define O_Production_PUBLIC_METHOD_6 blocks, void *
#define O_Production_PUBLIC_METHOD_7 blocks_p, bool
#define O_Production_PUBLIC_METHOD_8 blocks_len, o_uint
#define O_Production_PUBLIC_METHOD_9 first_init, void
#define O_Production_PUBLIC_METHOD_10 first, void *
#define O_Production_PUBLIC_METHOD_11 follow_init, void
#define O_Production_PUBLIC_METHOD_12 follow, void *
#define O_Production_PUBLIC_METHOD_13 subset, void *
#define O_Production_PUBLIC_METHOD_14 union_set, void *
#define O_Production_PUBLIC_METHOD_15 traversed, void *
#define O_Production_PUBLIC_METHOD_16 traversed_by_p, bool, (void * ancestor, ancestor)
#define O_Production_PUBLIC_METHOD_17 done_p, bool
#define O_Production_PUBLIC_METHOD_18 set_done, void, (bool done, done)
#define O_Production_PUBLIC_METHOD_19 set_type, void, (enum NT_TYPE type, type)
#define O_Production_PUBLIC_METHOD_20 type, enum NT_TYPE
#define O_Production_PUBLIC_METHOD_21 set_id, void, (o_uint id, id)
#define O_Production_PUBLIC_METHOD_22 id, o_uint
#define O_Production_PUBLIC_METHOD_23 set_epsilon, void, (bool epsilon, epsilon)
#define O_Production_PUBLIC_METHOD_24 epsilon, bool
#define O_Production_PUBLIC_METHOD_25 clear_set, void
#define O_Production_ctor O_Production_OVERRIDE_METHOD_0
#define O_Production_dtor O_Production_OVERRIDE_METHOD_1
#define O_Production_inspect O_Production_OVERRIDE_METHOD_2
#define O_Production_no O_Production_PUBLIC_METHOD_0
#define O_Production_tokens O_Production_PUBLIC_METHOD_1
#define O_Production_tokens_len O_Production_PUBLIC_METHOD_2
#define O_Production_add_token O_Production_PUBLIC_METHOD_3
#define O_Production_block O_Production_PUBLIC_METHOD_4
#define O_Production_create_block O_Production_PUBLIC_METHOD_5
#define O_Production_blocks O_Production_PUBLIC_METHOD_6
#define O_Production_blocks_p O_Production_PUBLIC_METHOD_7
#define O_Production_blocks_len O_Production_PUBLIC_METHOD_8
#define O_Production_first_init O_Production_PUBLIC_METHOD_9
#define O_Production_first O_Production_PUBLIC_METHOD_10
#define O_Production_follow_init O_Production_PUBLIC_METHOD_11
#define O_Production_follow O_Production_PUBLIC_METHOD_12
#define O_Production_subset O_Production_PUBLIC_METHOD_13
#define O_Production_union_set O_Production_PUBLIC_METHOD_14
#define O_Production_traversed O_Production_PUBLIC_METHOD_15
#define O_Production_traversed_by_p O_Production_PUBLIC_METHOD_16
#define O_Production_done_p O_Production_PUBLIC_METHOD_17
#define O_Production_set_done O_Production_PUBLIC_METHOD_18
#define O_Production_set_type O_Production_PUBLIC_METHOD_19
#define O_Production_type O_Production_PUBLIC_METHOD_20
#define O_Production_set_id O_Production_PUBLIC_METHOD_21
#define O_Production_id O_Production_PUBLIC_METHOD_22
#define O_Production_set_epsilon O_Production_PUBLIC_METHOD_23
#define O_Production_epsilon O_Production_PUBLIC_METHOD_24
#define O_Production_clear_set O_Production_PUBLIC_METHOD_25
O_DEF_GLOBAL_METHODS()

#endif
