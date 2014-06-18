#ifndef NONTERMINAL_STRCUT_H
#define NONTERMINAL_STRCUT_H

#include <libooc/object.struct.h>
#include "nonterminal.h"

struct Nonterminal {
    struct Object super;
    void * self;
    void * productions;
    enum NT_TYPE type;
    ooc_uint id;
};

def_class_struct()

#endif
