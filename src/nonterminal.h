#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <libooc/object.h>

enum NT_TYPE {
    NOT_SET,
    PRESENT,
    BLANK
};

#undef CLASS
#define CLASS Nonterminal
#define _Nonterminal_PUBLIC_OVERRIDE_METHODS \
    (_Nonterminal_ctor), \
    (_Nonterminal_dtor), \
    (_Nonterminal_hash_code)
#define _Nonterminal_PUBLIC_METHODS \
    (_Nonterminal_token), \
    (_Nonterminal_productions), \
    (_Nonterminal_create_production), \
    (_Nonterminal_last_production), \
    (_Nonterminal_set_type), \
    (_Nonterminal_type), \
    (_Nonterminal_set_id), \
    (_Nonterminal_id)
#define _Nonterminal_PRIVATE_METHODS
#define _Nonterminal_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Nonterminal_dtor dtor, void
#define _Nonterminal_hash_code hash_code, size_t
#define _Nonterminal_token token, void *
#define _Nonterminal_productions productions, void *
#define _Nonterminal_create_production create_production, void *
#define _Nonterminal_last_production last_production, void *
#define _Nonterminal_set_type set_type, void, (enum NT_TYPE type, type)
#define _Nonterminal_type type, enum NT_TYPE
#define _Nonterminal_set_id set_id, void, (size_t id, id)
#define _Nonterminal_id id, size_t
def_public_methods()

#endif
