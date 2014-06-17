#ifndef TERMINAL_STRCUT_H
#define TERMINAL_STRCUT_H

#include <libooc/object.struct.h>
#include "terminal.h"

struct Terminal {
    struct Object super;
    void * self;
    size_t id;
};

def_class_struct()

#endif
