#ifndef BLOCK_H
#define BLOCK_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Block
#define _Block_PUBLIC_OVERRIDE_METHODS \
    (_Block_ctor), \
    (_Block_dtor), \
    (_Block_inspect)
#define _Block_PUBLIC_METHODS \
    (_Block_set_id), \
    (_Block_id), \
    (_Block_no), \
    (_Block_tokens), \
    (_Block_add_token), \
    (_Block_expand)
#define _Block_PRIVATE_METHODS
#define _Block_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Block_dtor dtor, void
#define _Block_inspect inspect, char *
#define _Block_set_id set_id, void, (ooc_uint id, id)
#define _Block_id id, ooc_uint
#define _Block_no no, ooc_uint
#define _Block_tokens tokens, void *
#define _Block_add_token add_token, void, (void * token, token)
#define _Block_expand expand, void
def_public_methods()

#endif
