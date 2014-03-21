#ifndef NONTERMINAL_STRCUT_H
#define NONTERMINAL_STRCUT_H

#include <libooc/object.struct.h>
#include "nonterminal.h"

struct Nonterminal {
    struct Object super;
    void * self;
    void * stmts;
};

def_class_struct()

#endif
