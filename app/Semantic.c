#include "Semantic.h"

void semantic(Tree *t) {
        setTree(t);
        PS_storeNTs(); // NT = NonTerminal
        PS_storeTs(); // T = Terminal
}

// Store NonTerminals functions

void PS_storeNTs() {
        if(tree->child != NULL) {
                enterWhichTree(&P_storeNTs, 0);
                enterWhichTree(&PS_storeNTs, 1);
        }
}

void P_storeNTs() {
        Token *t = getChild(0)->token; // child[0]->token is a NonTerminal.
        storeNT(t);
        freeMemory(t);
}

// Store Terminals functions

static int P_count = 0;

void PS_storeTs() {
        if(tree->child != NULL) {
                enterWhichTree(&P_storeTs, 0);
                P_count++;
                enterWhichTree(&PS_storeTs, 1);
        }
}

void P_storeTs() {
        enterWhichTree(&STMTS_storeTs, 2);
}

static int STMTS__count = 0;

void STMTS_storeTs() {
        enterWhichTree(&TOKENS_storeTs, 0);
        STMTS__count++;
        enterWhichTree(&STMTS__storeTs, 1);
}

void STMTS__storeTs() {
        if(tree->child != NULL) {
                enterWhichTree(&TOKENS_storeTs, 1);
                STMTS__count++;
                enterWhichTree(&STMTS__storeTs, 2);
        }
}

void TOKENS_storeTs() {
        if(tree->child != NULL) {
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
