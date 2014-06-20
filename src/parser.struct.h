#ifndef PARSER_STRUCT_H
#define PARSER_STRUCT_H

#include <libooc/object.struct.h>
#include "parser.h"

struct Parser {
    struct Object super;
    void * scanner;
    void * token;
    enum TYPE type;
};

O_DEF_CLASS_STRUCT()

#endif
