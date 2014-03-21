#ifndef TABLE_BUILDER_STRCUT_H
#define TABLE_BUILDER_STRCUT_H

#include <libooc/object.struct.h>
#include "table_builder.h"

struct TableBuilder {
    struct Object super;
    void * nonterminals;
    void * terminals;
};

def_class_struct()

#endif
