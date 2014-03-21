#ifndef SCANNER_STRUCT_H
#define SCANNER_STRUCT_H

#include <libooc/object.struct.h>
#include "scanner.h"

struct Scanner {
    struct Object super;
    char * string;
    char * forward;
    char * lexeme;
    void * token;
};

def_class_struct()

#endif
