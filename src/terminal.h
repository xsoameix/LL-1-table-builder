#ifndef TERMINAL_H
#define TERMINAL_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Terminal
#define _Terminal_PUBLIC_OVERRIDE_METHODS \
    (_Terminal_ctor), \
    (_Terminal_dtor), \
    (_Terminal_inspect)
#define _Terminal_PUBLIC_METHODS \
    (_Terminal_set_id), \
    (_Terminal_id)
#define _Terminal_PRIVATE_METHODS
#define _Terminal_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Terminal_dtor dtor, void
#define _Terminal_inspect inspect, char *
#define _Terminal_set_id set_id, void, (ooc_uint id, id)
#define _Terminal_id id, ooc_uint
def_public_methods()

#endif
