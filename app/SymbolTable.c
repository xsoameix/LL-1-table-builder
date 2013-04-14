#include "SymbolTable.h"

// Element type is NonTerminal.
static Array *gNT; // g = global variable

// Element type is Terminal.
static Array *gT; // g = global variable

void storeNT(Token *t) {
        addNT(t);
}

void storeT(Token *t) {
        addT(t);
}

void storeInWhichP(int NT_i, int P_i, int type, Token *tk) {
        Symbol *s = NULL;
        if(type == NONTERMINAL) {
                NonTerminal *n = gNT->item[NT_IndexOf(gNT, tk->id)];
                s = newS_NT(n);
        } else {
                Terminal *t = gT->item[T_IndexOf(gT, tk->id)];
                s = newS_T(t);
        }
        addInWhichP(NT_i, P_i, s);
}

void addInWhichP(int NT_i, int P_i, Symbol *s) {
        NonTerminal *n = gNT->item[NT_i];
        if(n->P->count < P_i + 1) {
                ArrayAdd(n->P, newP(s));
        } else {
                ArrayAdd(((Production*) n->P->item[P_i])->S, s);
        }
}

// NonTerminal utilities

void addNT(Token *t) {
        if(gNT == NULL) {
                gNT = ArrayNew(1);
        }
        ArrayAdd(gNT, newNT(t));
}

NonTerminal* newNT(Token *t) {
        NonTerminal *n = (NonTerminal*) newMemory(sizeof(NonTerminal));
        n->no = gNT->count;
        n->id = t->id;
        n->P = ArrayNew(1);
        return n;
}

int NT_IndexOf(Array *a, char *id) {
        for(int i = 0; i < a->count; i++) {
                if(strcmp(((NonTerminal*) a->item[i])->id, id) == 0) {
                        return i;
                }
        }
        return -1;
}

bool isNT(Token *t) {
        assert(gNT != NULL);
        for(int i = 0; i < gNT->count; i++) {
                if(strcmp(((NonTerminal*) gNT->item[i])->id, t->id) == 0) {
                        return true;
                }
        }
        return false;
}

// Terminal utilities

void addT(Token *t) {
        if(gT == NULL) {
                gT = ArrayNew(1);
        }
        ArrayAdd(gT, newT(t));
}

Terminal* newT(Token *token) {
        Terminal *t = (Terminal*) newMemory(sizeof(Terminal));
        t->no = gT->count;
        t->id = token->id;
        return t;
}

int T_IndexOf(Array *a, char *id) {
        for(int i = 0; i < a->count; i++) {
                if(strcmp(((Terminal*) a->item[i])->id, id) == 0) {
                        return i;
                }
        }
        return -1;
}

// Symbol utilities

Symbol* newS_NT(NonTerminal *n) { // S = Symbol
        Symbol *s = (Symbol*) newMemory(sizeof(Symbol));
        s->type = NONTERMINAL;
        s->NT = n;
        s->T = NULL;
        return s;
}

Symbol* newS_T(Terminal *t) { // S = Symbol
        Symbol *s = (Symbol*) newMemory(sizeof(Symbol));
        s->type = TERMINAL;
        s->NT = NULL;
        s->T = t;
        return s;
}


// Producion utilities

Production* newP(Symbol *s) { // P = Production
        Production *p = (Production*) newMemory(sizeof(Production));
        p->S = ArrayNew(1);
        ArrayAdd(p->S, s);
        return p;
}
