#include "Parser.h"

/* syntax:
 * PS -> P PS | epsilon
 * P -> NT "->" STMTS
 * STMTS -> TOKENS STMTS'
 * STMTS' -> '|' TOKENS STMTS' | epsilon
 * TOKENS -> TOKEN TOKENS | epsilon
 */

char *scanningFile;

Token *lookaheadToken;
int lookahead;

int space = 0;

void parse(char *file) {
        scanningFile = file;
        next();
        parse_PS();
}

void parse_PS() {
        printSpaces();
        printf("parse_PS\n");
        if(lookahead == NT) {
                parse_P();
                parse_PS();
        } else if(lookahead == EOF) {
        } else {
                syntaxError();
        }
        space--;
}

void parse_P() {
        printSpaces();
        printf("parse_P\n");
        if(lookahead == NT) {
                match(NT);
                match(ARROW);
                parse_STMTS();
        } else {
                syntaxError();
        }
        space--;
}

void parse_STMTS() {
        printSpaces();
        printf("parse_STMTS\n");
        parse_TOKENS();
        parse_STMTS_();
        space--;
}

void parse_STMTS_() {
        printSpaces();
        printf("parse_STMTS_\n");
        if(lookahead == OR) {
                match(OR);
                parse_TOKENS();
                parse_STMTS_();
        } else if(lookahead == NT || lookahead == EOF) {
        } else {
                syntaxError();
        }
        space--;
}

void parse_TOKENS() {
        printSpaces();
        printf("parse_SYMBOLS\n");
        if(lookahead == TOKEN) {
                match(TOKEN);
                parse_TOKENS();
        }
        space--;
}

void match(int c) {
        if(lookahead == c) {
                next();
        } else {
                syntaxError();
        }
}

void next() {
        lookaheadToken = scan(scanningFile);
        if(lookaheadToken == NULL) {
                lookahead = EOF;
        } else {
                lookahead = lookaheadToken->type;
                printf("lookahead: %s\n", lookaheadToken->id);
        }
}

void syntaxError() {
        printf("Syntax error\n");
        exit(0);
}

void printSpaces() {
        for(int i = 0; i < space; i++) {
                printf("\t");
        }
        space++;
}
