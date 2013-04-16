#include "Semantic.h"

static void PS_storeNTs();
static void P_storeNTs();
static void PS_storeTs();
static void P_storeTs();
static void STMTS_storeTs();
static void STMTS__storeTs();
static void TOKENS_storeTs();

// Usage: put NonTerminals and Terminals into SymbolTable.

void semantic(Tree *t) {
        setTree(t);
        PS_storeNTs(); // NT = NonTerminal
        PS_storeTs(); // T = Terminal
}

// Store NonTerminals functions
// Usage: To store NonTerminals into SymbolTable.

static
void PS_storeNTs() {
        if(getTree()->child != NULL) {
                enterWhichTree(&P_storeNTs, 0);
                enterWhichTree(&PS_storeNTs, 1);
        }
}

static
void P_storeNTs() {
        Token *t = getChild(0)->token; // child[0]->token is a NonTerminal.
        storeNT(t);
        freeMemory(t);
}

// Store Terminals functions
// Usage: To store Terminals into SymbolTable.

static int P_count = 0; // The number of NonTerminals.

static
void PS_storeTs() {
        if(getTree()->child != NULL) {
                enterWhichTree(&P_storeTs, 0);
                P_count++;
                enterWhichTree(&PS_storeTs, 1);
        }
}

static
void P_storeTs() {
        freeMemory(getChild(1)->token);
        enterWhichTree(&STMTS_storeTs, 2);
}

static int STMTS__count = 0; // The number of Production of the certain NonTerminal.

static
void STMTS_storeTs() {
        enterWhichTree(&TOKENS_storeTs, 0);
        STMTS__count++;
        enterWhichTree(&STMTS__storeTs, 1);
        STMTS__count--;
}

static
void STMTS__storeTs() {
        if(getTree()->child != NULL) {
                freeMemory(getChild(0)->token);
                enterWhichTree(&TOKENS_storeTs, 1);
                STMTS__count++;
                enterWhichTree(&STMTS__storeTs, 2);
                STMTS__count--;
        }
}

static
void TOKENS_storeTs() {
        if(getTree()->child != NULL) {
                Token *t = getChild(0)->token; // child[0] is a token.
                if(isNT(t)) {
                        storeInWhichP(P_count, STMTS__count, NONTERMINAL, t); // P = Production
                } else {
                        storeT(t);
                        storeInWhichP(P_count, STMTS__count, TERMINAL, t); // P = Production
                }
                freeMemory(t);
                enterWhichTree(&TOKENS_storeTs, 1);
        }
}
