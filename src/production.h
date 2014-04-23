#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Production
#define _Production_PUBLIC_OVERRIDE_METHODS \
    (_Production_ctor), \
    (_Production_dtor), \
    (_Production_inspect)
#define _Production_PUBLIC_METHODS \
    (_Production_no), \
    (_Production_set_tokens), \
    (_Production_tokens), \
    (_Production_first_init), \
    (_Production_first), \
    (_Production_follow_init), \
    (_Production_follow), \
    (_Production_subset), \
    (_Production_union_set), \
    (_Production_traversed), \
    (_Production_traversed_by_p), \
    (_Production_done_p), \
    (_Production_set_done), \
    (_Production_set_type), \
    (_Production_type), \
    (_Production_set_id), \
    (_Production_id), \
    (_Production_set_epsilon), \
    (_Production_epsilon), \
    (_Production_clear_set)
#define _Production_PRIVATE_METHODS
#define _Production_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Production_dtor dtor, void
#define _Production_inspect inspect, char *
#define _Production_no no, size_t
#define _Production_set_tokens set_tokens, void, (void * tokens, tokens)
#define _Production_tokens tokens, void *
#define _Production_first_init first_init, void
#define _Production_first first, void *
#define _Production_follow_init follow_init, void
#define _Production_follow follow, void *
#define _Production_subset subset, void *
#define _Production_union_set union_set, void *
#define _Production_traversed traversed, void *
#define _Production_traversed_by_p traversed_by_p, bool, (void * ancestor, ancestor)
#define _Production_done_p done_p, bool
#define _Production_set_done set_done, void, (bool done, done)
#define _Production_set_type set_type, void, (enum NT_TYPE type, type)
#define _Production_type type, enum NT_TYPE
#define _Production_set_id set_id, void, (size_t id, id)
#define _Production_id id, size_t
#define _Production_set_epsilon set_epsilon, void, (bool epsilon, epsilon)
#define _Production_epsilon epsilon, bool
#define _Production_clear_set clear_set, void
def_public_methods()

#endif
