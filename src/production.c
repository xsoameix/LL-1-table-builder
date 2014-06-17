#include <stdlib.h>
#include <libooc/hash.h>
#include <libooc/array.h>

#include "nonterminal.h"
#include "block.h"
#include "production.struct.h"

def_class(Production, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->nonterminal = va_arg(* args_ptr, void *);
    self->no = va_arg(* args_ptr, size_t);
    self->tokens = NULL;
    self->blocks = NULL;
    self->epsilon = false;
    self->done = false;
}

static void
delete_each_token(void * null, void * token, size_t index) {
    delete(token);
}

static void
delete_each_block(void * null, void * block, size_t index) {
    delete(block);
}

override
def(dtor, void) {
    Array_each(self->tokens, delete_each_token, NULL);
    delete(self->tokens);
    if(self->blocks != NULL) {
        Array_each(self->blocks, delete_each_block, NULL);
        delete(self->blocks);
    }
    delete(self->first);
    delete(self->follow);
    free(self);
}

override
def(inspect, char *) {
    return Object_inspect(Nonterminal_token(self->nonterminal));
}

def(no, size_t) {
    return self->no;
}

def(reverse_each_token, void : void (* @iter)(void * _self_, void * obj, size_t index) . void * @_self_) {
    Array_reverse_each(self->tokens, iter, _self_);
}

def(tokens, void *) {
    if(self->tokens == NULL) {
        self->tokens = new(Array);
    }
    return self->tokens;
}

def(tokens_size, size_t) {
    return Array_len(self->tokens);
}

def(add_token, void : void * @token) {
    void * tokens = Production_tokens(self);
    Array_push(tokens, token);
}

def(block, void * : size_t @index) {
    return self->blocks == NULL ? NULL : Array_get(self->blocks, index);
}

def(each_block, void : void (* @iter)(void * _self_, void * obj, size_t index) . void * @_self_) {
    if(self->blocks != NULL) {
        Array_each(self->blocks, iter, _self_);
    }
}

def(create_block, void *) {
    void * blocks = Production_blocks(self);
    void * tokens = Production_tokens(self);
    size_t len = Array_len(tokens);
    void * block = new(Block, len);
    Array_push(blocks, block);
    return block;
}

def(blocks, void *) {
    if(self->blocks == NULL) {
        self->blocks = new(Array);
    }
    return self->blocks;
}

def(blocks_size, size_t) {
    return self->blocks == NULL ? 0 : Array_len(self->blocks);
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

def(clear_set, void) {
    delete(self->subset);
    delete(self->union_set);
    delete(self->traversed);
}
