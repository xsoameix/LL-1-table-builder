#include <stdlib.h>
#include <stdio.h>
#include <libooc/array.h>

#include "token.h"
#include "scanner.h"
#include "nonterminal.h"
#include "production.h"
#include "block.h"
#include "parser.struct.h"

def_class(Parser, Object)

override
def(ctor, void : va_list * @args_ptr) {
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
// BLOCK'     : OPEN_BRACE ANY_TOKEN CLOSE_BRACE
// ANY_TOKEN  : NONTERMINAL ANY_TOKEN
//            | DEFINE      ANY_TOKEN
//            | TOKEN       ANY_TOKEN
//            | BLOCK'      ANY_TOKEN
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
// BLOCK'     |                          OPEN_BRACE
// ANY_TOKEN  | NONTERMI... DEF... TO... BLOCK' ... epsilon     O. SP... PADD...             NEXT_L...

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
        match(self, NONTERMINAL);
        discard(self, DEFINE);
        parse_TOKENS(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// TOKENS     :               TOKEN TOKENS'
//            | BLOCK PADDING TOKEN TOKENS'

def(parse_TOKENS, void : void * @nonterminal) {
    if(self->type == TOKEN) {
        void * production = Nonterminal_create_production(nonterminal);
        Production_add_token(production, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, nonterminal);
    } else if(self->type == OPEN_BRACE) {
        void * production = Nonterminal_create_production(nonterminal);
        parse_BLOCK(self, production);
        discard(self, PADDING);
        Production_add_token(production, self->token);
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
        discard(self, SPACE);
        parse_TOKENS__(self, nonterminal);
    } else if(self->type == PADDING) {
        discard(self, PADDING);
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
        void * production = Nonterminal_last_production(nonterminal);
        parse_BLOCK(self, production);
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
        discard(self, PADDING);
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
        void * production = Nonterminal_last_production(nonterminal);
        Production_add_token(production, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, nonterminal);
    } else if(self->type == OR) {
        discard(self, OR);
        parse_TOKENS(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

// BLOCK      : OPEN_BRACE ANY_TOKEN CLOSE_BRACE

def(parse_BLOCK, void : void * @production) {
    if(self->type == OPEN_BRACE) {
        void * block = Production_create_block(production);
        discard(self, OPEN_BRACE);
        parse_ANY_TOKEN(self, block);
        discard(self, CLOSE_BRACE);
    } else {
        syntax_error(self);
    }
}

// BLOCK'     : OPEN_BRACE ANY_TOKEN CLOSE_BRACE

def(parse_BLOCK_, void : void * @block) {
    if(self->type == OPEN_BRACE) {
        Block_add_token(block, self->token);
        match(self, OPEN_BRACE);
        parse_ANY_TOKEN(self, block);
        Block_add_token(block, self->token);
        match(self, CLOSE_BRACE);
    } else {
        syntax_error(self);
    }
}

// ANY_TOKEN  : NONTERMINAL ANY_TOKEN
//            | DEFINE      ANY_TOKEN
//            | TOKEN       ANY_TOKEN
//            | BLOCK'      ANY_TOKEN
//            | OR          ANY_TOKEN
//            | SPACE       ANY_TOKEN
//            | PADDING     ANY_TOKEN
//            | NEXT_LINE   ANY_TOKEN
//            | epsilon

def(parse_ANY_TOKEN, void : void * @block) {
    if(self->type == NONTERMINAL) {
        Block_add_token(block, self->token);
        match(self, NONTERMINAL);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == DEFINE) {
        Block_add_token(block, self->token);
        match(self, DEFINE);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == TOKEN) {
        Block_add_token(block, self->token);
        match(self, TOKEN);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == OPEN_BRACE) {
        parse_BLOCK_(self, block);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == OR) {
        Block_add_token(block, self->token);
        match(self, OR);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == SPACE) {
        Block_add_token(block, self->token);
        match(self, SPACE);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == PADDING) {
        Block_add_token(block, self->token);
        match(self, PADDING);
        parse_ANY_TOKEN(self, block);
    } else if(self->type == NEXT_LINE) {
        Block_add_token(block, self->token);
        match(self, NEXT_LINE);
        parse_ANY_TOKEN(self, block);
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

private
def(discard, void : enum TYPE @expected) {
    if(self->type == expected) {
        delete(self->token);
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
