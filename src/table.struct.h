#ifndef TABLE_STRCUT_H
#define TABLE_STRCUT_H

#include <libooc/object.struct.h>
#include "table.h"

struct Table {
    struct Object super;
    void * nonterminals;
    void * nonterminal_set;
    void * terminals;
    void * terminal_set;
};

def_class_struct()

#endif
