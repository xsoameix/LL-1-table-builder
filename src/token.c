#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <libooc/string.conflict.h>
#include <libooc/inttype.h>

#include "scanner.h"
#include "token.struct.h"

static void
ctor_call(void * self, ...) {
    va_list args;
    va_start(args, self);
    ctor(self, &args);
    va_end(args);
}

O_DEF_CLASS(Token, Object, O_CLASS_SIZE_VARIABLE)

override
def(ctor, void : va_list * @args_ptr) {
    enum TYPE type = va_arg(* args_ptr, enum TYPE);
    char * chars = va_arg(* args_ptr, char *);
    uint_t size = va_arg(* args_ptr, uint_t);
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
    char * chars = inspect(self->string);
    if(!chars_allocated_by_ctor(self, chars)) {
        free(chars);
    }
    free(self);
}

private
def(chars_allocated_by_ctor, bool : char * @chars) {
    const struct ObjectClass * string_class = String;
    return chars == (void *) self + sizeof(struct Token) + string_class->size;
}

override
def(equals, bool : void * @obj) {
    return String_equals(self->string, ((struct Token *) obj)->string);
}

override
def(hash_code, uint_t) {
    return String_hash_code(self->string);
}

override
def(inspect, char *) {
    return inspect(self->string);
}

def(type, enum TYPE) {
    return self->type;
}

def(set, void : void * @string) {
    String_set(self->string, string);
}

def(strip, void) {
    String_strip(self->string);
}

static bool
alpha_p(void * null, char c) {
    return isalpha(c);
}

def(lstrip, char *) {
    char * chars = inspect(self->string);
    uint_t i = String_index(self->string, alpha_p, NULL);
    return chars + i;
}
