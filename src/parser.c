#include <stdlib.h>
#include <stdio.h>
#include <libooc/array.h>

#include "token.h"
#include "scanner.h"
#include "nonterminal.h"
#include "production.h"
#include "parser.struct.h"

def_class(Parser, Object)

override
def(ctor, void : va_list * @args_ptr) {
    Nonterminal_init();
    Production_init();
    self->scanner = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

def(parse, void *) {
    next(self);
    void * nonterminals = new(Array);
    parse_NTS(self, nonterminals);
    return nonterminals;
}

// syntax (use BNF):
// NTS        : NT NTS
//            | END_OF_FILE
// NT         : NONTERMINAL DEFINE TOKENS
// TOKENS     :               TOKEN TOKENS'
//            | BLOCK PADDING TOKEN TOKENS'
// TOKENS'    : SPACE TOKENS''
//            | PADDING TOKENS''''
//            | epsilon
// TOKENS''   : BLOCK TOKENS'''
//            | TOKENS''''
// TOKENS'''  : PADDING TOKENS''''
//            | epsilon
// TOKENS'''' : TOKEN TOKENS'
//            | OR TOKENS
// BLOCK      : OPEN_BRACE ANY_TOKEN CLOSE_BRACE
// ANY_TOKEN  : NONTERMINAL ANY_TOKEN
//            | DEFINE      ANY_TOKEN
//            | TOKEN       ANY_TOKEN
//            | BLOCK       ANY_TOKEN
//            | OR          ANY_TOKEN
//            | SPACE       ANY_TOKEN
//            | PADDING     ANY_TOKEN
//            | NEXT_LINE   ANY_TOKEN
//            | epsilon

// examples:
// NONTERMINAL DEFINE [BLOCK PADDING] TOKEN [SPACE BLOCK PADDING]|[PADDING]|SPACE OR
//                    [BLOCK PADDING] TOKEN [SPACE BLOCK PADDING]|[PADDING]|SPACE TOKEN
//                                          [SPACE BLOCK PADDING]|[PADDING]|SPACE OR
//                    [BLOCK PADDING] TOKEN [SPACE BLOCK PADDING]|[PADDING]|SPACE TOKEN
//                                          [SPACE BLOCK PADDING]|[PADDING]|SPACE TOKEN
//                                          [SPACE BLOCK]
// NONTERMINAL DEFINE [BLOCK PADDING] TOKEN

// tokens:
// NONTERMINAL: TERM (S* TERM)*
//              TOKEN
// DEFINE     : ':'
// TOKEN
// OPEN_BRACE : '{'
// CLOSE_BRACE: '}'
// OR         : '|'
// SPACE(S)   : ' '
// PADDING    : TERM (S|TERM)* S
// END_OF_FILE: TERM (S* TERM)*
//              EOF
//            | EOF
// NEXT_LINE  : TERM (S|TERM)* (?!S|EOF|TOKEN)

// ll1 table:
//              NONTERMINAL DEFINE TOKEN OPEN_BRACE CLOSE_BRACE OR SPACE PADDING END_OF_FILE NEXT_LINE
//              =========== ====== ===== ========== =========== == ===== ======= =========== =========
// NTS        | NT NTS                                                           END_OF_FILE
// NT         | NONTERMI...
// TOKENS     |                    TO... BLOCK P...
// TOKENS'    | epsilon                                            SP... PADD... epsilon
// TOKENS''   |                    TO... BLOCK T...             T.
// TOKENS'''  | epsilon                                                  PADD... epsilon
// TOKENS'''' |                    TO...                        O.
// BLOCK      |                          OPEN_BRACE
// ANY_TOKEN  | NONTERMI... DEF... TO... BLOCK A... epsilon     O. SP... PADD...             NEXT_L...

// NTS        : NT NTS
//            | END_OF_FILE

def(parse_NTS, void : void * @nonterminals) {
    if(self->type == NONTERMINAL) {
        parse_NT(self, nonterminals);
        parse_NTS(self, nonterminals);
    } else if(self->type == END_OF_FILE) {
        match(self, END_OF_FILE);
    } else {
        syntax_error(self);
    }
}

// NT         : NONTERMINAL DEFINE TOKENS

def(parse_NT, void : void * @nonterminals) {
    if(self->type == NONTERMINAL) {
        void * nonterminal = new(Nonterminal, self->token);
        Array_push(nonterminals, nonterminal);
        void * productions = new(Array);
        Nonterminal_set_productions(nonterminal, productions);
        match(self, NONTERMINAL);
        match(self, DEFINE);
        parse_TOKENS(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// TOKENS     :               TOKEN TOKENS'
//            | BLOCK PADDING TOKEN TOKENS'

def(parse_TOKENS, void : void * @nonterminal) {
    if(self->type == TOKEN) {
        void * productions = Nonterminal_productions(nonterminal);
        size_t len = Array_len(productions);
        void * production = new(Production, nonterminal, len);
        Array_push(productions, production);
        void * tokens = new(Array);
        Production_set_tokens(production, tokens);
        Array_push(tokens, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, nonterminal);
    } else if(self->type == OPEN_BRACE) {
        void * productions = Nonterminal_productions(nonterminal);
        size_t len = Array_len(productions);
        void * production = new(Production, nonterminal, len);
        Array_push(productions, production);
        void * tokens = new(Array);
        Production_set_tokens(production, tokens);
        parse_BLOCK(self, productions);
        match(self, PADDING);
        Array_push(tokens, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// TOKENS'    : SPACE TOKENS''
//            | PADDING TOKENS''''
//            | epsilon

def(parse_TOKENS_, void : void * @nonterminal) {
    if(self->type == SPACE) {
        match(self, SPACE);
        parse_TOKENS__(self, nonterminal);
    } else if(self->type == PADDING) {
        match(self, PADDING);
        parse_TOKENS____(self, nonterminal);
    } else if(self->type == NONTERMINAL ||
            self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
}

// TOKENS''   : BLOCK TOKENS'''
//            | TOKENS''''

def(parse_TOKENS__, void : void * @nonterminal) {
    if(self->type == OPEN_BRACE) {
        parse_BLOCK(self, nonterminal);
        parse_TOKENS___(self, nonterminal);
    } else if(self->type == TOKEN ||
            self->type == OR) {
        parse_TOKENS____(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// TOKENS'''  : PADDING TOKENS''''
//            | epsilon

def(parse_TOKENS___, void : void * @nonterminal) {
    if(self->type == PADDING) {
        match(self, PADDING);
        parse_TOKENS____(self, nonterminal);
    } else if(self->type == NONTERMINAL ||
            self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
}

// TOKENS'''' : TOKEN TOKENS'
//            | OR TOKENS

def(parse_TOKENS____, void : void * @nonterminal) {
    if(self->type == TOKEN) {
        void * productions = Nonterminal_productions(nonterminal);
        void * production = Array_last(productions);
        void * tokens = Production_tokens(production);
        Array_push(tokens, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, nonterminal);
    } else if(self->type == OR) {
        match(self, OR);
        parse_TOKENS(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// BLOCK      : OPEN_BRACE ANY_TOKEN CLOSE_BRACE

def(parse_BLOCK, void : void * @nonterminal) {
    if(self->type == OPEN_BRACE) {
        match(self, OPEN_BRACE);
        parse_ANY_TOKEN(self, nonterminal);
        match(self, CLOSE_BRACE);
    } else {
        syntax_error(self);
    }
}

// ANY_TOKEN  : NONTERMINAL ANY_TOKEN
//            | DEFINE      ANY_TOKEN
//            | TOKEN       ANY_TOKEN
//            | BLOCK       ANY_TOKEN
//            | OR          ANY_TOKEN
//            | SPACE       ANY_TOKEN
//            | PADDING     ANY_TOKEN
//            | NEXT_LINE   ANY_TOKEN
//            | epsilon

def(parse_ANY_TOKEN, void : void * @nonterminal) {
    if(self->type == NONTERMINAL) {
        match(self, NONTERMINAL);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == DEFINE) {
        match(self, DEFINE);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == TOKEN) {
        match(self, TOKEN);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == OPEN_BRACE) {
        parse_BLOCK(self, nonterminal);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == OR) {
        match(self, OR);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == SPACE) {
        match(self, SPACE);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == PADDING) {
        match(self, PADDING);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == NEXT_LINE) {
        match(self, NEXT_LINE);
        parse_ANY_TOKEN(self, nonterminal);
    } else if(self->type == CLOSE_BRACE) {
    } else {
        syntax_error(self);
    }
}

private
def(match, void : enum TYPE @expected) {
    if(self->type == expected) {
        next(self);
    } else {
        syntax_error(self);
    }
}

def(next, void) {
    Scanner_scan(self->scanner);
    self->token = Scanner_token(self->scanner);
    if(self->token == NULL) {
        self->type = END_OF_FILE;
    } else {
        self->type = Token_type(self->token);
    }
}

def(syntax_error, void) {
    puts("syntax error");
    exit(0);
}
