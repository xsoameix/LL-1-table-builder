#include <stdlib.h>
#include <libooc/inttype.h>

#include "terminal.struct.h"

def_class(Terminal, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->self = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

override
def(inspect, char *) {
    return inspect(self->self);
}

def(set_id, void : uint_t @id) {
    self->id = id;
}

def(id, uint_t) {
    return self->id;
}
