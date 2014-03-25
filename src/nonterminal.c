#include <stdlib.h>
#include <libooc/array.h>
#include <libooc/hash.h>

#include "token.h"
#include "nonterminal.struct.h"

def_class(Nonterminal, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->self = va_arg(* args_ptr, void *);
    self->type = NOT_SET;
}

override
def(dtor, void) {
    free(self);
}

override
def(hash_code, size_t) {
    void * string = Token_string(self->self);
    return hash_code(string);
}

def(token, void *) {
    return self->self;
}

def(set_productions, void : void * @productions) {
    self->productions = productions;
}

def(productions, void *) {
    return self->productions;
}

def(set_type, void : enum NT_TYPE @type) {
    self->type = type;
}

def(type, enum NT_TYPE) {
    return self->type;
}
