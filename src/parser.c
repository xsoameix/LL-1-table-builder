#include <stdlib.h>
#include <stdio.h>
#include <libooc/array.h>

#include "token.h"
#include "scanner.h"
#include "nonterminal.h"
#include "parser.struct.h"

def_class(Parser, Object)

override
def(ctor, void : va_list * @args_ptr) {
    Nonterminal_init();
    self->scanner = va_arg(* args_ptr, void *);
}

override
def(dtor, void) {
    free(self);
}

def(parse, void *) {
    next(self);
    void * nonterminals = parse_NTS(self);
    return nonterminals;
}

// syntax (use BNF):
// NTS -> NT NTS' | NEXT_LINE END_OF_FILE | END_OF_FILE
// NTS' -> NEXT_LINE NTS'' | END_OF_FILE
// NTS'' -> NT NTS' | END_OF_FILE
// NT -> TOKEN ARROW STMTS
// STMTS -> TOKENS STMTS'
// STMTS' -> OR TOKENS STMTS' | epsilon
// TOKENS -> TOKEN TOKENS'
// TOKENS' -> TOKEN TOKENS' | epsilon

// ll1 table:
//           TOKEN             ARROW OR               NEXT_LINE             END_OF_FILE
//           ================= ===== ================ ===============       =============
// NTS     | NT NTS'                                  NEXT_LINE END_OF_FILE END_OF_FILE
// NTS'    |                                          NEXT_LINE NTS''       END_OF_FILE
// NTS''   | NT NTS'                                                        END_OF_FILE
// NT      | TOKEN ARROW STMTS
// STMTS   | TOKENS STMTS'
// STMTS'  |                         OR TOKENS STMTS' epsilon               epsilon
// TOKENS  | TOKEN TOKENS'
// TOKENS' | TOKEN TOKENS'           epsilon          epsilon               epsilon

// abstract syntax tree (use EBNF):
// NTS -> { NT };
// NT -> TOKEN { STMT };
//        ^--- nonterminal
// STMT -> TOKEN { TOKEN };
//           ^--------^--- terminals or nonterminals

def(parse_NTS, void *) {
    void * nonterminals;
    if(self->type == TOKEN) {
        nonterminals = new(Array);
        parse_NT(self, nonterminals);
        parse_NTS_(self, nonterminals);
    } else if(self->type == NEXT_LINE) {
        match(self, NEXT_LINE);
    } else if(self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
    return nonterminals;
}

// NTS ->
//     {
//         nonterminals = new(Array);
//     }
//     NT NTS'
//   | NEXT_LINE END_OF_FILE
//   | END_OF_FILE
// NTS' -> NEXT_LINE NTS'' | END_OF_FILE
// NTS'' -> NT NTS' | END_OF_FILE
// NT ->
//     {
//          void * nonterminal = new(Nonterminal, self->token);
//          Array_push(nonterminals, nonterminal);
//     }
//     TOKEN ARROW STMTS
// STMTS ->
//     {
//          void * stmts = new(Array);
//          Nonterminal_set_stmts(nonterminal, stmts);
//     }
//     TOKENS STMTS'
// STMTS' -> OR TOKENS STMTS' | epsilon
// TOKENS ->
//     {
//          void * tokens = new(Array);
//          Array_push(stmts, tokens);
//          Array_push(tokens, self->token);
//     }
//     TOKEN TOKENS'
// TOKENS' ->
//     {
//          Array_push(tokens, self->token);
//     }
//     TOKEN TOKENS' | epsilon

def(parse_NTS_, void : void * @nonterminals) {
    if(self->type == NEXT_LINE) {
        match(self, NEXT_LINE);
        parse_NTS__(self, nonterminals);
    } else if(self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
}

def(parse_NTS__, void : void * @nonterminals) {
    if(self->type == TOKEN) {
        parse_NT(self, nonterminals);
        parse_NTS_(self, nonterminals);
    } else if(self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
}

def(parse_NT, void : void * @nonterminals) {
    if(self->type == TOKEN) {
        void * nonterminal = new(Nonterminal, self->token);
        Array_push(nonterminals, nonterminal);
        match(self, TOKEN);
        match(self, ARROW);
        parse_STMTS(self, nonterminal);
    } else {
        syntax_error(self);
    }
}

def(parse_STMTS, void : void * @nonterminal) {
    if(self->type == TOKEN) {
        void * stmts = new(Array);
        Nonterminal_set_stmts(nonterminal, stmts);
        parse_TOKENS(self, stmts);
        parse_STMTS_(self, stmts);
    } else {
        syntax_error(self);
    }
}

def(parse_STMTS_, void : void * @stmts) {
    if(self->type == OR) {
        match(self, OR);
        parse_TOKENS(self, stmts);
        parse_STMTS_(self, stmts);
    } else if(self->type == NEXT_LINE ||
            self->type == END_OF_FILE) {
    } else {
        syntax_error(self);
    }
}

def(parse_TOKENS, void : void * @stmts) {
    if(self->type == TOKEN) {
        void * tokens = new(Array);
        Array_push(stmts, tokens);
        Array_push(tokens, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, tokens);
    } else {
        syntax_error(self);
    }
}

def(parse_TOKENS_, void : void * @tokens) {
    if(self->type == TOKEN) {
        Array_push(tokens, self->token);
        match(self, TOKEN);
        parse_TOKENS_(self, tokens);
    } else if(self->type == OR ||
            self->type == NEXT_LINE ||
            self->type == END_OF_FILE) {
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
