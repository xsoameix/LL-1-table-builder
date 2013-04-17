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
        freeMemoryLog(t, mS_nT);
}

// Store Terminals functions
// Usage: To store Terminals into SymbolTable.

static int P_count = 0; // The number of NonTerminals.

static
void PS_storeTs() {
        Tree *tree = getTree();
        if(tree->child != NULL) {
                enterWhichTree(&P_storeTs, 0);
                P_count++;
                enterWhichTree(&PS_storeTs, 1);
                mArrayFree(tree->child, NULL, mAC_AN);
        }
        freeMemoryLog(tree, m_nT);
}

static
void P_storeTs() {
        Tree *tree = getTree();
        mFreeToken(getChild(1)->token);
        freeMemoryLog(getChild(0), mAL_nL);
        freeMemoryLog(getChild(1), mAL_nL);
        enterWhichTree(&STMTS_storeTs, 2);
        mArrayFree(tree->child, NULL, mAL_AN);
        freeMemoryLog(tree, m_nT);
}

static int STMTS__count = 0; // The number of Production of the certain NonTerminal.

static
void STMTS_storeTs() {
        Tree *tree = getTree();
        enterWhichTree(&TOKENS_storeTs, 0);
        STMTS__count++;
        enterWhichTree(&STMTS__storeTs, 1);
        STMTS__count--;
        mArrayFree(tree->child, NULL, mAC_AN);
        freeMemoryLog(tree, m_nT);
}

static
void STMTS__storeTs() {
        Tree *tree = getTree();
        if(tree->child != NULL) {
                mFreeToken(getChild(0)->token);
                freeMemoryLog(getChild(0), mAL_nL);
                enterWhichTree(&TOKENS_storeTs, 1);
                STMTS__count++;
                enterWhichTree(&STMTS__storeTs, 2);
                STMTS__count--;
                mArrayFree(tree->child, NULL, mAL_AN);
        }
        freeMemoryLog(tree, m_nT);
}

static
void TOKENS_storeTs() {
        Tree *tree = getTree();
        if(tree->child != NULL) {
                Token *t = getChild(0)->token; // child[0] is a token.
                freeMemoryLog(getChild(0), mAL_nL);
                if(isNT(t)) {
                        storeInWhichP(P_count, STMTS__count, NONTERMINAL, t); // P = Production
                        enterWhichTree(&TOKENS_storeTs, 1);
                        mFreeToken(t);
                } else {
                        storeT(t);
                        storeInWhichP(P_count, STMTS__count, TERMINAL, t); // P = Production
                        enterWhichTree(&TOKENS_storeTs, 1);
                        freeMemoryLog(t, mS_nT);
                }
                mArrayFree(tree->child, NULL, mAL_AN);
        }
        freeMemoryLog(tree, m_nT);
}
