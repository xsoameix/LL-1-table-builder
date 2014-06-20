#ifndef O_TOKEN_H
#define O_TOKEN_H

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


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Token
#define O_PARENT Object
#define O_Token_OVERRIDE_METHODS_LEN 5
#define O_Token_PUBLIC_METHODS_LEN 4
#define O_Token_PRIVATE_METHODS_LEN 1
#define O_Token_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Token_OVERRIDE_METHOD_1 dtor, void
#define O_Token_OVERRIDE_METHOD_2 equals, bool, (void * obj, obj)
#define O_Token_OVERRIDE_METHOD_3 hash_code, ooc_uint
#define O_Token_OVERRIDE_METHOD_4 inspect, char *
#define O_Token_PUBLIC_METHOD_0 type, enum TYPE
#define O_Token_PUBLIC_METHOD_1 set, void, (void * string, string)
#define O_Token_PUBLIC_METHOD_2 strip, void
#define O_Token_PUBLIC_METHOD_3 lstrip, char *
#define O_Token_PRIVATE_METHOD_0 chars_allocated_by_ctor, bool, (char * chars, chars)
#define O_Token_ctor O_Token_OVERRIDE_METHOD_0
#define O_Token_dtor O_Token_OVERRIDE_METHOD_1
#define O_Token_equals O_Token_OVERRIDE_METHOD_2
#define O_Token_hash_code O_Token_OVERRIDE_METHOD_3
#define O_Token_inspect O_Token_OVERRIDE_METHOD_4
#define O_Token_type O_Token_PUBLIC_METHOD_0
#define O_Token_set O_Token_PUBLIC_METHOD_1
#define O_Token_strip O_Token_PUBLIC_METHOD_2
#define O_Token_lstrip O_Token_PUBLIC_METHOD_3
#define O_Token_chars_allocated_by_ctor O_Token_PRIVATE_METHOD_0
O_DEF_GLOBAL_METHODS()

#endif
