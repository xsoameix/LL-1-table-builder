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
    o_uint * table;
    o_uint   rows;
    o_uint   cols;

    o_uint * rhs;
    o_uint   rhs_len;

    o_uint * prhs;
    o_uint   prhs_len;
};

O_DEF_CLASS_STRUCT()

#endif
