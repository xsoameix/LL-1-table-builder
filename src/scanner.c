#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <libooc/string.conflict.h>

#include "token.struct.h"
#include "scanner.struct.h"

def_class(Scanner, Object)

override
def(ctor, void : va_list * @args_ptr) {
    Token_init();
    void * content = va_arg(* args_ptr, void *);
    char * string = inspect(content);
    self->string = string;
    self->forward = string;
    self->lexeme = string;
}

override
def(dtor, void) {
    free(self);
}

def(scan, void) {
    char * forward = self->forward;
    char * lexeme = self->lexeme;
    ignore_spaces(self, &forward, &lexeme);
    enum TYPE type;
    if(alpha_or_punct_p(self, * forward)) {
        type = TOKEN;
        do {
            forward += 1;
        } while(alpha_or_punct_p(self, * forward));
    } else if(arrow_p(self, forward)) {
        type = ARROW;
        forward += 2;
    } else if(or_p(self, * forward)) {
        type = OR;
        forward += 1;
    } else if(next_line_p(self, * forward)) {
        type = NEXT_LINE;
        forward += 1;
    } else if(EOF_p(self, * forward)) {
        self->token = NULL;
        return;
    }
    self->forward = forward;
    self->lexeme = forward;
    self->token = new(Token, type, lexeme, forward - lexeme);
}

def(ignore_spaces, void : char ** @forward . char ** @lexeme) {
    while(space_p(self, ** forward)) {
        * forward += 1;
        * lexeme += 1;
    }
}

def(space_p, bool : char @c) {
    return c == ' ' || c == '\t';
}

def(alpha_or_punct_p, bool : char @c) {
    return (isalpha(c) ||
            (c >= 0x21 && c <= 0x2C) || // !"#$%&'()*+,
            (c >= 0x2E && c <= 0x2F) || // ./
            (c >= 0x3A && c <= 0x40) || // :;<=>?@
            (c >= 0x5B && c <= 0x60) || // [\]^_`
            (c == 0x7B) ||              // {
            (c >= 0x7D && c <= 0x7E));  // }~
}

def(arrow_p, bool : char * @string) {
    return strncmp(string, "->", 2) == 0;
}

def(or_p, bool : char @c) {
    return c == '|';
}

def(next_line_p, bool : char @c) {
    return c == 0x0A || c == 0x0D;
}

def(EOF_p, bool : char @c) {
    return c == '\0';
}

def(token, void *) {
    return self->token;
}
