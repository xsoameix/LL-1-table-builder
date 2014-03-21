#ifndef TOKEN_STRUCT_H
#define TOKEN_STRUCT_H

#include <libooc/object.struct.h>
#include "token.h"

struct Token {
    struct Object super;
    enum TYPE type;
    void * string;
};

def_class_struct()

#endif
