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
    (_Nonterminal_set_stmts), \
    (_Nonterminal_stmts), \
    (_Nonterminal_set_type), \
    (_Nonterminal_type), \
    (_Nonterminal_first_init), \
    (_Nonterminal_first), \
    (_Nonterminal_follow_init), \
    (_Nonterminal_follow), \
    (_Nonterminal_subset), \
    (_Nonterminal_union_set), \
    (_Nonterminal_traversed), \
    (_Nonterminal_traversed_by_p), \
    (_Nonterminal_done_p), \
    (_Nonterminal_set_done)
#define _Nonterminal_PRIVATE_METHODS
#define _Nonterminal_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Nonterminal_dtor dtor, void
#define _Nonterminal_hash_code hash_code, size_t
#define _Nonterminal_token token, void *
#define _Nonterminal_set_stmts set_stmts, void, (void * stmts, stmts)
#define _Nonterminal_stmts stmts, void *
#define _Nonterminal_set_type set_type, void, (enum NT_TYPE type, type)
#define _Nonterminal_type type, enum NT_TYPE
#define _Nonterminal_first_init first_init, void
#define _Nonterminal_first first, void *
#define _Nonterminal_follow_init follow_init, void
#define _Nonterminal_follow follow, void *
#define _Nonterminal_subset subset, void *
#define _Nonterminal_union_set union_set, void *
#define _Nonterminal_traversed traversed, void *
#define _Nonterminal_traversed_by_p traversed_by_p, bool, (void * ancestor, ancestor)
#define _Nonterminal_done_p done_p, bool
#define _Nonterminal_set_done set_done, void, (bool done, done)
def_public_methods()

#endif
