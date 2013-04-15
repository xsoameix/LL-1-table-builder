#include "Parser.h"

/* syntax:
 * PS -> P PS | epsilon
 * P -> NT "->" STMTS
 * STMTS -> TOKENS STMTS'
 * STMTS' -> '|' TOKENS STMTS' | epsilon
 * TOKENS -> TOKEN TOKENS | epsilon
 */

static void parse_PS();
static void parse_P();
static void parse_STMTS();
static void parse_STMTS_();
static void parse_TOKENS();
static void match(int c);
static void next();
static void syntaxError();

static char *scanningFile;

static Token *lookaheadToken;
static int lookahead;

Tree* parse(char *file) {
        scanningFile = file;
        next();
        Tree *t = buildRoot(&parse_PS, "PS");
        freeMemory(file);
        return t;
}

static
void parse_PS() {
        if(lookahead == NONTERMINAL) {
                buildTree(&parse_P, "P");
                buildTree(&parse_PS, "PS");
        } else if(lookahead == EOF) {
        } else {
                syntaxError();
        }
}

static
void parse_P() {
        if(lookahead == NONTERMINAL) {
                match(NONTERMINAL);
                match(ARROW);
                buildTree(&parse_STMTS, "STMTS");
        } else {
                syntaxError();
        }
}

static
void parse_STMTS() {
        buildTree(&parse_TOKENS, "TOKENS");
        buildTree(&parse_STMTS_, "STMTS_");
}

static
void parse_STMTS_() {
        if(lookahead == OR) {
                match(OR);
                buildTree(&parse_TOKENS, "TOKENS");
                buildTree(&parse_STMTS_, "STMTS_");
        } else if(lookahead == NONTERMINAL || lookahead == EOF) {
        } else {
                syntaxError();
        }
}

static
void parse_TOKENS() {
        if(lookahead == TOKEN) {
                match(TOKEN);
                buildTree(&parse_TOKENS, "TOKENS");
        }
}

static
void match(int c) {
        if(lookahead == c) {
                addLeaf(lookaheadToken);
                next();
        } else {
                syntaxError();
        }
}

static
void next() {
        lookaheadToken = scan(scanningFile);
        if(lookaheadToken == NULL) {
                lookahead = EOF;
        } else {
                lookahead = lookaheadToken->type;
        }
}

static
void syntaxError() {
        printf("Syntax error\n");
        exit(0);
}
