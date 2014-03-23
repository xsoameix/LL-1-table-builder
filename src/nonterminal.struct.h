#ifndef NONTERMINAL_STRCUT_H
#define NONTERMINAL_STRCUT_H

#include <libooc/object.struct.h>
#include "nonterminal.h"

struct Nonterminal {
    struct Object super;
    void * self;
    void * stmts;
    enum NT_TYPE type;
    void * first;
    void * follow;

    // for tree traverse
    void * subset;
    void * union_set;
    void * traversed;
    bool done;
};

def_class_struct()

#endif
