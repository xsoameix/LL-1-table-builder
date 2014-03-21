#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Nonterminal
#define _Nonterminal_PUBLIC_OVERRIDE_METHODS \
    (_Nonterminal_ctor), \
    (_Nonterminal_dtor), \
    (_Nonterminal_hash_code)
#define _Nonterminal_PUBLIC_METHODS \
    (_Nonterminal_token), \
    (_Nonterminal_set_stmts), \
    (_Nonterminal_stmts)
#define _Nonterminal_PRIVATE_METHODS
#define _Nonterminal_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Nonterminal_dtor dtor, void
#define _Nonterminal_hash_code hash_code, size_t
#define _Nonterminal_token token, void *
#define _Nonterminal_set_stmts set_stmts, void, (void * stmts, stmts)
#define _Nonterminal_stmts stmts, void *
def_public_methods()

#endif
