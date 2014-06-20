#ifndef O_NONTERMINAL_H
#define O_NONTERMINAL_H

#include <libooc/object.h>
#include "nonterminal_type.h"


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Nonterminal
#define O_PARENT Object
#define O_Nonterminal_OVERRIDE_METHODS_LEN 3
#define O_Nonterminal_PUBLIC_METHODS_LEN 8
#define O_Nonterminal_PRIVATE_METHODS_LEN 0
#define O_Nonterminal_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Nonterminal_OVERRIDE_METHOD_1 dtor, void
#define O_Nonterminal_OVERRIDE_METHOD_2 hash_code, ooc_uint
#define O_Nonterminal_PUBLIC_METHOD_0 token, void *
#define O_Nonterminal_PUBLIC_METHOD_1 productions, void *
#define O_Nonterminal_PUBLIC_METHOD_2 create_production, void *
#define O_Nonterminal_PUBLIC_METHOD_3 last_production, void *
#define O_Nonterminal_PUBLIC_METHOD_4 set_type, void, (enum NT_TYPE type, type)
#define O_Nonterminal_PUBLIC_METHOD_5 type, enum NT_TYPE
#define O_Nonterminal_PUBLIC_METHOD_6 set_id, void, (ooc_uint id, id)
#define O_Nonterminal_PUBLIC_METHOD_7 id, ooc_uint
#define O_Nonterminal_ctor O_Nonterminal_OVERRIDE_METHOD_0
#define O_Nonterminal_dtor O_Nonterminal_OVERRIDE_METHOD_1
#define O_Nonterminal_hash_code O_Nonterminal_OVERRIDE_METHOD_2
#define O_Nonterminal_token O_Nonterminal_PUBLIC_METHOD_0
#define O_Nonterminal_productions O_Nonterminal_PUBLIC_METHOD_1
#define O_Nonterminal_create_production O_Nonterminal_PUBLIC_METHOD_2
#define O_Nonterminal_last_production O_Nonterminal_PUBLIC_METHOD_3
#define O_Nonterminal_set_type O_Nonterminal_PUBLIC_METHOD_4
#define O_Nonterminal_type O_Nonterminal_PUBLIC_METHOD_5
#define O_Nonterminal_set_id O_Nonterminal_PUBLIC_METHOD_6
#define O_Nonterminal_id O_Nonterminal_PUBLIC_METHOD_7
O_DEF_GLOBAL_METHODS()

#endif
