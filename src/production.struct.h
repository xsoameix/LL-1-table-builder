#ifndef PRODUCTION_STRCUT_H
#define PRODUCTION_STRCUT_H

#include <libooc/object.struct.h>
#include "production.h"

struct Production {
    struct Object super;
    void * nonterminal;
    size_t no;
    void * tokens;
    void * first;
    void * follow;
    enum NT_TYPE type;

    // for tree traverse
    void * subset;
    void * union_set;
    void * traversed;
    bool done;
};

def_class_struct()

#endif
