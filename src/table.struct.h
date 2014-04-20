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
    size_t * table;
    size_t * rhs;
    size_t   rhs_size;
    size_t * prhs;
    size_t   prhs_size;
};

def_class_struct()

#endif
