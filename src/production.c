#include <stdlib.h>
#include <libooc/hash.h>

#include "nonterminal.h"
#include "production.struct.h"

def_class(Production, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->nonterminal = va_arg(* args_ptr, void *);
    self->no = va_arg(* args_ptr, size_t);
    self->epsilon = false;
    self->done = false;
}

override
def(dtor, void) {
    free(self);
}

override
def(inspect, char *) {
    return Object_inspect(Nonterminal_token(self->nonterminal));
}

def(no, size_t) {
    return self->no;
}

def(set_tokens, void : void * @tokens) {
    self->tokens = tokens;
}

def(tokens, void *) {
    return self->tokens;
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

def(follow_init, void) {
    delete(self->subset);
    delete(self->union_set);
    delete(self->traversed);
    self->follow = new(Hash);
    self->subset = new(Hash);
    self->union_set = new(Hash);
    self->traversed = new(Hash);
}

def(follow, void *) {
    return self->follow;
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

def(set_epsilon, void : bool @epsilon) {
    self->epsilon = epsilon;
}

def(epsilon, bool) {
    return self->epsilon;
}
