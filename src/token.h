#ifndef TOKEN_H
#define TOKEN_H

#include <libooc/object.h>

enum TYPE {
    NONTERMINAL = 256,
    DEFINE,
    TOKEN,
    OPEN_BRACE,
    CLOSE_BRACE,
    OR,
    SPACE,
    PADDING,
    END_OF_FILE,
    NEXT_LINE
};

#undef CLASS
#define CLASS Token
#define _Token_PUBLIC_OVERRIDE_METHODS \
    (_Token_ctor), \
    (_Token_dtor), \
    (_Token_equals), \
    (_Token_hash_code), \
    (_Token_inspect)
#define _Token_PUBLIC_METHODS \
    (_Token_type), \
    (_Token_set), \
    (_Token_strip), \
    (_Token_lstrip)
#define _Token_PRIVATE_METHODS \
    (_Token_chars_allocated_by_ctor)
#define _Token_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Token_dtor dtor, void
#define _Token_chars_allocated_by_ctor chars_allocated_by_ctor, bool, (char * chars, chars)
#define _Token_equals equals, bool, (void * obj, obj)
#define _Token_hash_code hash_code, ooc_uint
#define _Token_inspect inspect, char *
#define _Token_type type, enum TYPE
#define _Token_set set, void, (void * string, string)
#define _Token_strip strip, void
#define _Token_lstrip lstrip, char *
def_public_methods()

#endif
