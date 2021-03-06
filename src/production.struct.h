#ifndef PRODUCTION_STRCUT_H
#define PRODUCTION_STRCUT_H

#include <libooc/object.struct.h>
#include "production.h"

struct Production {
    struct Object super;
    void * nonterminal;
    o_uint no;
    void * tokens;
    void * blocks;
    void * first;
    void * follow;
    enum NT_TYPE type;
    o_uint id;
    bool epsilon;

    // for tree traverse
    void * subset;
    void * union_set;
    void * traversed;
    bool done;
};

O_DEF_CLASS_STRUCT()

#endif
