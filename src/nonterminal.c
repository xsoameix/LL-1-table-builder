#include <stdlib.h>
#include <libooc/array.h>
#include <libooc/hash.h>

#include "token.h"
#include "production.h"
#include "nonterminal.struct.h"

def_class(Nonterminal, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->self = va_arg(* args_ptr, void *);
    self->productions = NULL;
    self->type = NOT_SET;
    Token_strip(self->self);
}

static void
delete_each_prod(void * null, void * production, size_t index) {
    delete(production);
}

override
def(dtor, void) {
    Array_each(self->productions, delete_each_prod, NULL);
    delete(self->productions);
    delete(self->self);
    free(self);
}

override
def(hash_code, size_t) {
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
    size_t len = Array_len(productions);
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

def(set_id, void : size_t @id) {
    self->id = id;
}

def(id, size_t) {
    return self->id;
}
