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

    // action table
    ooc_uint * table;
    ooc_uint   rows;
    ooc_uint   cols;

    ooc_uint * rhs;
    ooc_uint   rhs_size;

    ooc_uint * prhs;
    ooc_uint   prhs_size;
};

def_class_struct()

#endif
