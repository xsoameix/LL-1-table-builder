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
    self->done = false;
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

def(set_type, void : enum NT_TYPE @type) {
    self->type = type;
}

def(type, enum NT_TYPE) {
    return self->type;
}

def(first_init, void) {
    self->first = new(Hash);
    self->subset = new(Hash);
    self->union_set = new(Hash);
    self->traversed = new(Hash);
}

def(first, void *) {
    return self->first;
}

def(subset, void *) {
    return self->subset;
}

def(union_set, void *) {
    return self->union_set;
}

def(traversed, void *) {
    return self->traversed;
}

def(traversed_by_p, bool : void * @ancestor) {
    void * set = union_set(ancestor);
    return Hash_intersact_p(self->traversed, set);
}

def(done_p, bool) {
    return self->done;
}

def(set_done, void : bool @done) {
    self->done = done;
}
