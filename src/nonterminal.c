#include <stdlib.h>
#include <libooc/array.h>
#include <libooc/hash.h>
#include <libooc/inttype.h>

#include "token.h"
#include "production.h"
#include "nonterminal.struct.h"

O_DEF_CLASS(Nonterminal, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->self = va_arg(* args_ptr, void *);
    self->productions = NULL;
    self->type = NOT_SET;
    Token_strip(self->self);
}

override
def(dtor, void) {

    void delete_each_prod(void * production, uint_t index) {
        delete(production);
    }

    Array_each(self->productions, delete_each_prod);
    delete(self->productions);
    delete(self->self);
    free(self);
}

override
def(hash_code, uint_t) {
    return hash_code(self->self);
}

def(token, void *) {
    return self->self;
}

def(productions, void *) {
    if(self->productions == NULL) {
        self->productions = new(Array);
    }
    return self->productions;
}

def(create_production, void *) {
    void * productions = Nonterminal_productions(self);
    uint_t len = Array_len(productions);
    void * production = new(Production, self, len);
    Array_push(productions, production);
    return production;
}

def(last_production, void *) {
    void * productions = Nonterminal_productions(self);
    return Array_last(productions);
}

def(set_type, void : enum NT_TYPE @type) {
    self->type = type;
}

def(type, enum NT_TYPE) {
    return self->type;
}

def(set_id, void : uint_t @id) {
    self->id = id;
}

def(id, uint_t) {
    return self->id;
}
