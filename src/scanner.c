#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <libooc/string.conflict.h>
#include <libooc/inttype.h>

#include "token.h"
#include "scanner.struct.h"

O_DEF_CLASS(Scanner, Object)

override
def(ctor, void : va_list * @args_ptr) {
    void * content = va_arg(* args_ptr, void *);
    char * string = inspect(content);
    self->string = string;
    self->forward = string;
    self->lexeme_start = string;
    self->lexeme_end = string;
}

override
def(dtor, void) {
    free(self);
}

def(scan, void) {
    char * forward = self->forward;
    char * lexeme_start = self->lexeme_start;
    char * lexeme_end = self->lexeme_end;
    enum TYPE type;
    if(token_p(self, * lexeme_end)) {
        if(lexeme_end == self->string) {
            type = NONTERMINAL;
            do {
                lexeme_end += 1;
            } while(token_p(self, * lexeme_end));
            do {
                lexeme_end += 1;
            } while(space_p(self, * lexeme_end));
        } else {
            type = TOKEN;
            do {
                lexeme_end += 1;
            } while(token_p(self, * lexeme_end));
        }
    } else if(space_p(self, * lexeme_end)) {
        type = SPACE;
        do {
            lexeme_end += 1;
        } while(space_p(self, * lexeme_end));
    } else if(open_brace_p(self, * lexeme_end)) {
        type = OPEN_BRACE;
        lexeme_end += 1;
    } else if(close_brace_p(self, * lexeme_end)) {
        type = CLOSE_BRACE;
        lexeme_end += 1;
    } else if(colon_p(self, * lexeme_end)) {
        type = DEFINE;
        do {
            lexeme_end += 1;
        } while(space_p(self, * lexeme_end));
    } else if(or_p(self, * lexeme_end)) {
        type = OR;
        do {
            lexeme_end += 1;
        } while(space_p(self, * lexeme_end));
    } else if(next_line_p(self, * lexeme_end)) {
        lexeme_end += 1;
        uint_t state = 0;
        while(true) {
            switch(state) {
            case 0:
                if(next_line_p(self, * lexeme_end)) {
                    lexeme_end += 1;
                } else if(EOF_p(self, * lexeme_end)) {
                    self->token = NULL;
                    return;
                } else if(token_p(self, * lexeme_end)) {
                    type = NONTERMINAL;
                    do {
                        lexeme_end += 1;
                    } while(token_p(self, * lexeme_end));
                    do {
                        lexeme_end += 1;
                    } while(space_p(self, * lexeme_end));
                    goto accept;
                } else if(space_p(self, * lexeme_end)) {
                    type = PADDING;
                    state = 1;
                    lexeme_end += 1;
                } else {
                    type = NEXT_LINE;
                    goto accept;
                }
                break;
            case 1:
                if(next_line_p(self, * lexeme_end)) {
                    state = 0;
                    lexeme_end += 1;
                } else if(space_p(self, * lexeme_end)) {
                    type = PADDING;
                    lexeme_end += 1;
                } else {
                    goto accept;
                }
                break;
            }
        }
        accept:;
    } else if(EOF_p(self, * lexeme_end)) {
        self->token = NULL;
        return;
    }
    self->forward = max(self, forward, lexeme_end);
    self->lexeme_start = self->forward;
    self->lexeme_end = self->forward;
    self->token = new(Token, type, lexeme_start, lexeme_end - lexeme_start);
}

def(max, char * : char * @z . char * @b) {
    return z > b ? z : b;
}

def(space_p, bool : char @c) {
    return c == ' ' || c == '\t';
}

def(token_p, bool : char @c) {
    return (isalpha(c) ||
            c >= 0x21 && c <= 0x2C || // !"#$%&'()*+,
            c >= 0x2D && c <= 0x2F || // -./
            c >= 0x30 && c <= 0x39 || // 0123456789
            c >= 0x3B && c <= 0x40 || // ;<=>?@
            c >= 0x5B && c <= 0x60 || // [\]^_`
            c == 0x7E);               // ~
}

def(open_brace_p, bool : char @c) {
    return c == '{';
}

def(close_brace_p, bool : char @c) {
    return c == '}';
}

def(colon_p, bool : char @c) {
    return c == ':';
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
