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

void parse(char *file) {
        scanningFile = file;
        next();
        buildRoot(&parse_PS, "PS");
}

void parse_PS() {
        if(lookahead == NT) {
                buildTree(&parse_P, "P");
                buildTree(&parse_PS, "PS");
        } else if(lookahead == EOF) {
        } else {
                syntaxError();
        }
}

void parse_P() {
        if(lookahead == NT) {
                match(NT);
                match(ARROW);
                buildTree(&parse_STMTS, "STMTS");
        } else {
                syntaxError();
        }
}

void parse_STMTS() {
        buildTree(&parse_TOKENS, "TOKENS");
        buildTree(&parse_STMTS_, "STMTS_");
}

void parse_STMTS_() {
        if(lookahead == OR) {
                match(OR);
                buildTree(&parse_TOKENS, "TOKENS");
                buildTree(&parse_STMTS_, "STMTS_");
        } else if(lookahead == NT || lookahead == EOF) {
        } else {
                syntaxError();
        }
}

void parse_TOKENS() {
        if(lookahead == TOKEN) {
                match(TOKEN);
                buildTree(&parse_TOKENS, "TOKENS");
        }
}

void match(int c) {
        if(lookahead == c) {
                addLeaf(lookaheadToken);
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
        }
}

void syntaxError() {
        printf("Syntax error\n");
        exit(0);
}
