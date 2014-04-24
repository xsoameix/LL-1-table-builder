#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libooc/array.h>
#include <libooc/string.conflict.h>

#include "token.h"
#include "block.struct.h"

def_class(Block, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->no = va_arg(* args_ptr, size_t);
    self->tokens = NULL;
}

override
def(dtor, void) {
    free(self);
}

override
def(inspect, char *) {
    void * token = Array_first(self->tokens);
    return inspect(token);
}

def(set_id, void : size_t @id) {
    self->id = id;
}

def(id, size_t) {
    return self->id;
}

def(tokens, void *) {
    if(self->tokens == NULL) {
        self->tokens = new(Array);
    }
    return self->tokens;
}

def(add_token, void : void * @token) {
    void * tokens = Block_tokens(self);
    Array_push(tokens, token);
}

struct compare {
    char * code;
    char * expand;
};

static void
expand_each_token(void * null, void * token, size_t index) {
    enum TYPE type = Token_type(token);
    if(!(type == NONTERMINAL || type == TOKEN)) {
        return;
    }
    struct compare scenarios[] = {
        {"pop()",  "Array_pop(as)"},
        {"push()", "Array_push(as, symbol)"},
        {NULL, NULL}
    };
    struct compare * scenario = scenarios;
    while(scenario->code != NULL) {
        size_t len = strlen(scenario->code);
        char * code = Token_lstrip(token);
        if(strncmp(code, scenario->code, len) == 0) {
            size_t remain = strlen(code) - len;
            size_t expand = strlen(scenario->expand);
            char * start = inspect(token);
            size_t offset = code - start;
            char * chars = malloc(offset + expand + remain + 1);
            chars[0] = '\0';
            strncat(chars, start, offset);
            strcat(chars, scenario->expand);
            strcat(chars, code + len);
            Token_set(token, chars);
            break;
        }
        scenario += 1;
    }
}

def(expand, void) {
    Array_each(self->tokens, expand_each_token, NULL);
}
