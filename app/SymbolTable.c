#include "SymbolTable.h"

void storeNT(Token *t) {
        addNT(t);
}

void storeT(Token *t) {
        addT(t);
}

// Usage: put NonTerminal or Terminal into the certain Production of the certain NonTerminal.

void storeInWhichP(int NT_i, int P_i, int type, Token *tk) {
        Symbol *s = NULL;
        if(type == NONTERMINAL) {
                NonTerminal *n = getNT()->item[NT_IndexOf(getNT(), tk->id)];
                s = newS_NT(n, mSIWP_nS_N);
        } else {
                Terminal *t = HGet(getT(), tk->id);
                s = newS_T(t, mSIWP_nS_T);
        }
        addInWhichP(NT_i, P_i, s);
}
