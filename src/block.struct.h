#ifndef BLOCK_STRCUT_H
#define BLOCK_STRCUT_H

#include <libooc/object.struct.h>
#include "block.h"

struct Block {
    struct Object super;
    void * tokens;
    ooc_uint no;
    ooc_uint id;
};

def_class_struct()

#endif
