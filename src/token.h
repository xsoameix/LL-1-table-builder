#ifndef TOKEN_H
#define TOKEN_H

#include <libooc/object.h>

enum TYPE {
    TOKEN = 256,
    ARROW,
    OR,
    NEXT_LINE,
    END_OF_FILE
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
    (_Token_string)
#define _Token_PRIVATE_METHODS
#define _Token_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Token_dtor dtor, void
#define _Token_equals equals, bool, (void * obj, obj)
#define _Token_hash_code hash_code, size_t
#define _Token_inspect inspect, char *
#define _Token_type type, enum TYPE
#define _Token_string string, void *
def_public_methods()

#endif
