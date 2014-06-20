#ifndef TERMINAL_STRCUT_H
#define TERMINAL_STRCUT_H

#include <libooc/object.struct.h>
#include "terminal.h"

struct Terminal {
    struct Object super;
    void * self;
    ooc_uint id;
};

O_DEF_CLASS_STRUCT()

#endif
