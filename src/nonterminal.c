#include <stdlib.h>
#include <libooc/array.h>

#include "token.h"
#include "nonterminal.struct.h"

def_class(Nonterminal, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->self = va_arg(* args_ptr, void *);
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

def(set_stmts, void : void * @stmts) {
    self->stmts = stmts;
}

def(stmts, void *) {
    return self->stmts;
}
