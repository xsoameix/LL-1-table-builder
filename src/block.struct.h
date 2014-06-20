#ifndef BLOCK_STRCUT_H
#define BLOCK_STRCUT_H

#include <libooc/object.struct.h>
#include "block.h"

struct Block {
    struct Object super;
    void * tokens;
    o_uint no;
    o_uint id;
};

O_DEF_CLASS_STRUCT()

#endif
