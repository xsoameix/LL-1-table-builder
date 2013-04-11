#include "Semantic.h"

void semantic(Tree *t) {
        setTree(t);
        enterTree(&semantic_PS);
}

void semantic_PS() {
        if(tree->child != NULL) {
                enterTree(&semantic_P);
        }
}

void semantic_P() {
        storeNonTerminal(getChildToken(0)); // token[0] is NonTerminal.
        enterTree(&semantic_STMTS);
}

void semantic_STMTS() {
        enterTree(&semantic_TOKENS);
        enterTree(&semantic_STMTS_);
}

void semantic_STMTS_() {
        if(tree->child != NULL) {
                enterTree(&semantic_TOKENS);
                enterTree(&semantic_STMTS_);
        }
}

void semantic_TOKENS() {
        if(tree->child != NULL) {
                storeToken(getChildToken(0)); // token[0] is a token.
        }
}
