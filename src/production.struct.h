#ifndef PRODUCTION_STRCUT_H
#define PRODUCTION_STRCUT_H

#include <libooc/object.struct.h>
#include "production.h"

struct Production {
    struct Object super;
    void * nonterminal;
    ooc_uint no;
    void * tokens;
    void * blocks;
    void * first;
    void * follow;
    enum NT_TYPE type;
    ooc_uint id;
    bool epsilon;

    // for tree traverse
    void * subset;
    void * union_set;
    void * traversed;
    bool done;
};

def_class_struct()

#endif
