#ifndef TABLEBUILDER_H
#define TABLEBUILDER_H

#include <libooc/object.h>


#undef CLASS
#define CLASS TableBuilder
#define _TableBuilder_PUBLIC_OVERRIDE_METHODS \
    (_TableBuilder_ctor), \
    (_TableBuilder_dtor)
#define _TableBuilder_PUBLIC_METHODS \
    (_TableBuilder_build)
#define _TableBuilder_PRIVATE_METHODS \
    (_TableBuilder_build_nonterminal_set), \
    (_TableBuilder_build_terminal_set), \
    (_TableBuilder_build_terminals)
#define _TableBuilder_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _TableBuilder_dtor dtor, void
#define _TableBuilder_build_nonterminal_set build_nonterminal_set, void, (struct Sets * sets, sets)
#define _TableBuilder_build_terminal_set build_terminal_set, void, (struct Sets * sets, sets)
#define _TableBuilder_build_terminals build_terminals, void
#define _TableBuilder_build build, void *
def_public_methods()

#endif
