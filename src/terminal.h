#ifndef O_TERMINAL_H
#define O_TERMINAL_H

#include <libooc/object.h>


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Terminal
#define O_PARENT Object
#define O_Terminal_OVERRIDE_METHODS_LEN 3
#define O_Terminal_PUBLIC_METHODS_LEN 2
#define O_Terminal_PRIVATE_METHODS_LEN 0
#define O_Terminal_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Terminal_OVERRIDE_METHOD_1 dtor, void
#define O_Terminal_OVERRIDE_METHOD_2 inspect, char *
#define O_Terminal_PUBLIC_METHOD_0 set_id, void, (ooc_uint id, id)
#define O_Terminal_PUBLIC_METHOD_1 id, ooc_uint
#define O_Terminal_ctor O_Terminal_OVERRIDE_METHOD_0
#define O_Terminal_dtor O_Terminal_OVERRIDE_METHOD_1
#define O_Terminal_inspect O_Terminal_OVERRIDE_METHOD_2
#define O_Terminal_set_id O_Terminal_PUBLIC_METHOD_0
#define O_Terminal_id O_Terminal_PUBLIC_METHOD_1
O_DEF_GLOBAL_METHODS()

#endif
