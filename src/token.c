#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libooc/string.conflict.h>

#include "token.struct.h"

static void
ctor_call(void * self, ...) {
    va_list args;
    va_start(args, self);
    ctor(self, &args);
    va_end(args);
}

def_class(Token, Object, CLASS_SIZE_VARIABLE)

override
def(ctor, void : va_list * @args_ptr) {
    enum TYPE type = va_arg(* args_ptr, enum TYPE);
    char * chars = va_arg(* args_ptr, char *);
    size_t size = va_arg(* args_ptr, size_t);
    const struct ObjectClass * string_class = String;
    void * p = malloc(sizeof(struct Token) + string_class->size + size + 1);

    struct Token * token = p;
    p += sizeof(struct Token); 
    struct Object * string = p;
    p += string_class->size;
    char * clone = p;

    // chars
    memcpy(clone, chars, size);
    clone[size] = '\0';

    // string
    string->class = String;
    ctor_call(string, clone);

    // token
    token->type = type;
    token->string = string;
    * (void **) self = token;
}

override
def(dtor, void) {
    free(self);
}

override
def(equals, bool : void * @obj) {
    return String_equals(self->string, ((struct Token *) obj)->string);
}

override
def(hash_code, size_t) {
    return String_hash_code(self->string);
}

override
def(inspect, char *) {
    return inspect(self->string);
}

def(type, enum TYPE) {
    return self->type;
}

def(string, void *) {
    return self->string;
}
